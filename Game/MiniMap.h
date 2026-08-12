#pragma once

class Player;

class MiniMap : public IGameObject
{
public:
    MiniMap();
    ~MiniMap();
    void Update();
    void Render(RenderContext& rc);

private:
    static const int MAX_CRYSTAL_DOTS = 16;  //多めに確保

    SpriteRender m_bgSprite;                       // ミニマップの背景(枠)
    SpriteRender m_playerDot;                      // プレイヤーを示すドット
    SpriteRender m_crystalDots[MAX_CRYSTAL_DOTS];  // クリスタルを示すドット

    Player* m_player = nullptr;

    Vector3 m_mapCenterPos = { -800.0f, -380.0f, 0.0f }; // ミニマップの中心座標(画面左下、要調整)
    float m_mapRadius = 100.0f;      // パネル自体の見た目の半径
    float m_dotClampRadius = 95.0f;  // 範囲外のクリスタルをこの半径以内に収める(パネルより少し小さめ)
    float m_worldRadius = 3000.0f;   // この距離までのクリスタルをマップに収める(遠いものは縁に張り付く)
};
