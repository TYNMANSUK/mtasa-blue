/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CObject.h
 *  PURPOSE:     Object entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/
#pragma once

// Kayl: There is now too many includes here, try to make it work with StdInc.h if possible
#include "CElement.h"
#include "CEvents.h"
#include "CObjectManager.h"

#include "CEasingCurve.h"
#include "TInterpolation.h"
#include "CPositionRotationAnimation.h"

class CObject : public CElement
{
    friend class CPlayer;

public:
    explicit CObject(CElement* pParent, class CObjectManager* pObjectManager, bool bIsLowLod);
    explicit CObject(const CObject& Copy);
    ~CObject(void);
    CElement* Clone(bool* bAddEntity, CResource* pResource) override;

    bool IsEntity(void) { return true; }

    void Unlink(void);

    const CVector& GetPosition(void);
    void           SetPosition(const CVector& vecPosition);

    void GetRotation(CVector& vecRotation);
    void SetRotation(const CVector& vecRotation);

    void GetMatrix(CMatrix& matrix);
    void SetMatrix(const CMatrix& matrix);

    bool                              IsMoving(void);
    void                              Move(const CPositionRotationAnimation& a_rMoveAnimation);
    void                              StopMoving(void);
    const CPositionRotationAnimation* GetMoveAnimation();

    unsigned char GetAlpha(void) { return m_ucAlpha; }
    void          SetAlpha(unsigned char ucAlpha) { m_ucAlpha = ucAlpha; }

    unsigned short GetModel(void) { return m_usModel; }
    void           SetModel(unsigned short usModel) { m_usModel = usModel; }

    const CVector& GetScale(void) { return m_vecScale; }
    void           SetScale(const CVector& vecScale) { m_vecScale = vecScale; }

    bool GetCollisionEnabled(void) { return m_bCollisionsEnabled; }
    void SetCollisionEnabled(bool bCollisionEnabled) { m_bCollisionsEnabled = bCollisionEnabled; }

    bool IsFrozen(void) { return m_bIsFrozen; }
    void SetFrozen(bool bFrozen) { m_bIsFrozen = bFrozen; }

    float GetHealth(void) { return m_fHealth; }
    void  SetHealth(float fHealth) { m_fHealth = fHealth; }

    bool IsSyncable(void) { return m_bSyncable; }
    void SetSyncable(bool bSyncable) { m_bSyncable = bSyncable; }

    CPlayer* GetSyncer(void) { return m_pSyncer; }
    void     SetSyncer(CPlayer* pPlayer);

    bool     IsLowLod(void);
    bool     SetLowLodObject(CObject* pLowLodObject);
    CObject* GetLowLodObject(void);

    bool IsVisibleInAllDimensions(void) { return m_bVisibleInAllDimensions; };
    void SetVisibleInAllDimensions(bool bVisible) { m_bVisibleInAllDimensions = bVisible; };

protected:
    bool ReadSpecialData(const int iLine) override;

private:
    CObjectManager* m_pObjectManager;
    CVector         m_vecRotation;
    unsigned char   m_ucAlpha;
    unsigned short  m_usModel;
    CVector         m_vecScale;
    bool            m_bIsFrozen;
    float           m_fHealth;
    bool            m_bBreakable;
    bool            m_bSyncable;
    CPlayer*        m_pSyncer;
    bool            m_bVisibleInAllDimensions = false;

protected:
    bool m_bCollisionsEnabled;

    const bool            m_bIsLowLod;                    // true if this object is low LOD
    CObject*              m_pLowLodObject;                // Pointer to low LOD version of this object
    std::vector<CObject*> m_HighLodObjectList;            // List of objects that use this object as a low LOD version

public:
    CPositionRotationAnimation* m_pMoveAnimation;
};
