#include "stdafx.h"
#include "MiniMap.h"
#include "Player.h"
#include "Crystal.h"
#include "GameState.h"
#include "MoveCrystal1.h"
#include "EscapeCrystal.h"
#include <vector>
#include <unordered_set>
MiniMap::MiniMap()
{
    m_bgSprite.Init("Assets/sprite/minimap_circle_v2.DDS", m_mapRadius * 2.0f, m_mapRadius * 2.0f);
    m_bgSprite.SetPosition(m_mapCenterPos);

    m_playerDot.Init("Assets/sprite/player_arrow.DDS", 20.0f, 20.0f);
    m_playerDot.SetPosition(m_mapCenterPos);
    

    // クリスタルドット(青く着色)
    for (int i = 0; i < MAX_CRYSTAL_DOTS; i++)
    {
        m_crystalDots[i].Init("Assets/sprite/crystal.dds", 20.0f, 20.0f);
        m_crystalDots[i].SetMulColor(Vector4(0.2f, 0.5f, 1.0f, 1.0f)); // 青色
    }

    m_player = FindGO<Player>("player");
}

MiniMap::~MiniMap()
{
}

void MiniMap::Update()
{
    if (m_player == nullptr)
    {
        m_player = FindGO<Player>("player");
        if (m_player == nullptr) return;
    }

    m_bgSprite.Update();

    // カメラの前方向・右方向を取得(Player::Move()と同じ考え方)
    // ※ループの外で1回だけ計算すればOK
    Vector3 camForward = g_camera3D->GetForward();
    camForward.y = 0.0f;
    float camForwardLen = camForward.Length();
    if (camForwardLen > 0.001f) camForward = camForward * (1.0f / camForwardLen);

    Vector3 camRight = g_camera3D->GetRight();
    camRight.y = 0.0f;
    float camRightLen = camRight.Length();
    if (camRightLen > 0.001f) camRight = camRight * (1.0f / camRightLen);

    // プレイヤーの向きをマップ空間(カメラ基準)に変換して矢印を回転
    Vector3 facing = m_player->facingDir;
    float rightComp = facing.x * camRight.x + facing.z * camRight.z;
    float upComp = facing.x * camForward.x + facing.z * camForward.z;
    float angleDeg = atan2f(rightComp, upComp) * (180.0f / 3.14159265f);

    Quaternion arrowRot;
    arrowRot.SetRotationDeg(Vector3::AxisZ, -angleDeg); // 符号は実機で見ながら調整
    m_playerDot.SetRotation(arrowRot);
    m_playerDot.Update();

    // 生き残っているクリスタルの座標を集める。
// Crystal/MoveCrystal1/EscapeCrystalは同じ"crystal"タグを持つが、
// 型ごとに別々にFindGOsを呼び、ポインタアドレスで重複を弾くことで
// 内部実装の挙動によらず確実に全種類・重複なしで拾う。
    std::vector<Vector3> crystalPositions;
    std::unordered_set<void*> seen;

    for (auto* c : FindGOs<Crystal>("crystal"))
    {
        if (c == nullptr) continue;
        void* addr = (void*)c;
        if (seen.count(addr)) continue;
        seen.insert(addr);
        crystalPositions.push_back(c->position);
    }
    for (auto* c : FindGOs<MoveCrystal1>("crystal"))
    {
        if (c == nullptr) continue;
        void* addr = (void*)c;
        if (seen.count(addr)) continue;
        seen.insert(addr);
        crystalPositions.push_back(c->position);
    }
    for (auto* c : FindGOs<EscapeCrystal>("crystal"))
    {
        if (c == nullptr) continue;
        void* addr = (void*)c;
        if (seen.count(addr)) continue;
        seen.insert(addr);
        crystalPositions.push_back(c->position);
    }

    int dotIndex = 0;
    for (auto& pos : crystalPositions)
    {
        if (dotIndex >= MAX_CRYSTAL_DOTS) break;

        // プレイヤーから各クリスタルへのXZ平面上のベクトル
        Vector3 diff = pos - m_player->position;
        diff.y = 0.0f;
        float dist = diff.Length();

        float mapRightN = 0.0f;
        float mapUpN = 0.0f;
        if (dist > 0.001f)
        {
            float dotRight = diff.x * camRight.x + diff.z * camRight.z;
            float dotForward = diff.x * camForward.x + diff.z * camForward.z;
            mapRightN = dotRight / dist;
            mapUpN = dotForward / dist;
        }

        float mapDist = (dist / m_worldRadius) * m_mapRadius;
        if (mapDist > m_dotClampRadius)
        {
            mapDist = m_dotClampRadius;
        }

        Vector3 dotPos = m_mapCenterPos;
        dotPos.x += mapRightN * mapDist;
        dotPos.y += mapUpN * mapDist;

        m_crystalDots[dotIndex].SetPosition(dotPos);
        m_crystalDots[dotIndex].Update();
        dotIndex++;
    }

    // 余ったドットは大きさ0にして実質非表示
    for (int i = dotIndex; i < MAX_CRYSTAL_DOTS; i++)
    {
        m_crystalDots[i].SetScale(Vector3::Zero);
        m_crystalDots[i].Update();
    }
}

void MiniMap::Render(RenderContext& rc)
{
    m_bgSprite.Draw(rc);
    m_playerDot.Draw(rc);
    for (int i = 0; i < MAX_CRYSTAL_DOTS; i++)
    {
        m_crystalDots[i].Draw(rc);
    }
}