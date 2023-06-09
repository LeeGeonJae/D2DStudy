#pragma once
#include "SceneComponent.h"

/*
    Render를 사용하는 컴포넌트를 위한 추상 클래스
    그리는 순서와, 그리는지 여부를 가진다.
    지금은 우선순위 없이 Render를 호출하고 있지만
    카메라 컬링 후에 실제 그리려는 자식클래스 인스턴스만
    자식클래스의 포인터 주소를 ZOrder로 정렬하여 그리도록 한다
*/

class RenderComponent :
    public SceneComponent
{
public:
    RenderComponent();
    virtual ~RenderComponent();

protected:
    int m_iZOrder;      // 그리는 순서
    bool m_bVisible;    // 그리려는지 여부

public:
    void SetZOrder(int zOrder) { m_iZOrder = zOrder; }
    void SetVisible(bool visible) { m_bVisible = visible; }

    virtual void Update(TimeManager* _TimeManager);
    virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

