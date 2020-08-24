#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

const double EPSILON = 1e-12;
ringsignList* insertRingsign(ringsignList* pRingList, int ringsign)
{
    ringsignList* pRingsignNew = new ringsignList;
    pRingsignNew->nRingsign = ringsign;
    pRingsignNew->pNext = NULL;
    //Neu list khong co phan tu nao
    if (pRingList == NULL)
    {
        return pRingsignNew;
    }
    //Neu list da co phan tu roi
    ringsignList* pTemp = pRingList;
    pTemp->pNext = pRingsignNew;
    return pRingsignNew;
}
int getBaseDamage(int opponentType)
{
    switch (opponentType)
    {
        case 1: return 10;     //Urukhai Monster
        case 2: return 18;     //Ring Ghost
        case 3: return 45;     //Strider
        case 4: return 82;     //Gollum
        case 5: return 75;     //Lurtz
        case 6: return 90;     //Gimli
        case 9: return 1;     //Saruman
        default:
            return 0;
    }
}
double getPowerofTen(int power)
{
    double product = 1.0;
    for (int i=1;i<=power;i++)
    {
        product*=10.0;
    }
    return product;
}
// double findMod(double a)
// {
//     double mod = a;
//     while (mod - 10.0 >= EPSILON)
//         mod = mod - 10.0;
//     return mod;
// }
// ringsignList* convertNumberToList(double number)
// {
//     double num = 0.0;
//     ringsignList* pRingsignHead = NULL;
//     ringsignList* pRingsignNew = NULL;
//     int count = 0;
//     while (number>EPSILON)
//     {
//         count++;
//         num = findMod(number);
//         number=number/10.0-num/10.0;
//         pRingsignNew = new ringsignList;
//         pRingsignNew->nRingsign = (int) num;
//         if (count==1)
//         {
//             pRingsignHead = pRingsignNew;
//             pRingsignNew->pNext = NULL;
//         }
//         else
//         {
//             pRingsignNew->pNext = pRingsignHead;
//             pRingsignHead = pRingsignNew;
//         }
//         pRingsignNew = NULL;
//     }
//     return pRingsignHead;
// }
ringsignList* getLastPointer(ringsignList* pRingListHead)
{
    if (pRingListHead==NULL) return NULL;
    ringsignList* pRingsignTemp = pRingListHead;
    while(pRingsignTemp->pNext!=NULL)
    {
        pRingsignTemp = pRingsignTemp->pNext;
    }
    return pRingsignTemp;
}
ringsignList* reverseList(ringsignList*pRingListHead)
{
    ringsignList* pRingListPre = pRingListHead;
    ringsignList* pRingListTemp = pRingListHead->pNext;
    ringsignList* pRingListPost = pRingListTemp;
    pRingListPre->pNext = NULL;
    while(pRingListTemp!=NULL)
    {
        pRingListPost=pRingListPost->pNext;
        pRingListTemp->pNext = pRingListPre;
        pRingListPre=pRingListTemp;
        pRingListTemp=pRingListPost;
    }
    return pRingListPre;
}
ringsignList* combat(knight& theKnight, eventList* pEvent)
{
	ringsignList* pRingListHead = NULL; // the pointer points to the head of the list
    ringsignList* pRingListTail = NULL; // the pointer points to the tail of the list
    int ringsignCount = 0;
    pRingListHead = insertRingsign(pRingListHead,theKnight.nInitRingsign);
    pRingListTail = pRingListHead;
    ringsignCount++;
	//fighting for honor and love here
	eventList* pEventTemp = NULL;
    int maxHP = theKnight.HP;
    int b = 0;
    int levelO = 0;        //level of opponent
    int ringsignO = 0;     //ringsign of opponent
    int eventOrder = 1;    //the order of event
    int eventCode = 0;
    int damage = 0;
    int opponentType = 0;
    ringsignList* pRingListTemp = NULL;
    bool isIsildur = false;
    bool isLegolas = false;
    bool isGandalf = false;
    if (maxHP == 777)       //Check the knight is Isildur ?
    {
        isIsildur = true;
    }
    else if (maxHP == 888)  //Check the knight is Legolas ?
    {
        isLegolas = true;
    }
    else if (maxHP == 999)  //Check the knight is Gandalf ?
    {
        isGandalf = true;
    }
    for (pEventTemp = pEvent, eventOrder=1; pEventTemp!=NULL; pEventTemp = pEventTemp->pNext,eventOrder++)
    {

        if (ringsignCount == 0) return NULL;

        eventCode = pEventTemp->nEventCode;
        if (eventCode == 0)
        {
            break;
        }
        else if (eventCode == 7)   //Arwen Fairy
        {
             pRingListTail = pRingListHead;
             pRingListHead = reverseList(pRingListHead);
             pRingListTemp = pRingListHead;
             int sum = 0;
             int reminder = 1;
             int num = 0;
             while(pRingListTemp->pNext!=NULL)
             {
                 num = pRingListTemp->nRingsign + reminder;
                 if (num>9)
                 {
                     pRingListTemp->nRingsign = num-10;
                     reminder = 1;
                 }
                 else
                 {
                     pRingListTemp->nRingsign = num;
                     reminder = 0;
                 }
                 pRingListTemp=pRingListTemp->pNext;
             }
             num = pRingListTemp->nRingsign + reminder;
             if (num>9)
             {
                pRingListTemp->nRingsign = num-10;
                ringsignList* pRingsignNew = new ringsignList;
                pRingsignNew->nRingsign = 1;
                pRingsignNew->pNext = NULL;
                pRingListTemp->pNext = pRingsignNew;
                pRingListTemp = pRingsignNew;
             }
             else
             {
                pRingListTemp->nRingsign = num;
                reminder = 0;
             }
             pRingListTail = pRingListHead;
             pRingListHead = reverseList(pRingListHead);
             while(pRingListHead != NULL && pRingListHead->nRingsign == 0)
             {
                 pRingListTemp = pRingListHead;
                 pRingListHead = pRingListHead->pNext;
                 delete pRingListTemp;
             }
             pRingListTail = getLastPointer(pRingListHead);
             pRingListTemp = NULL;
//             pRingListTail = NULL;
//             double num = 0.0;
//             while (pRingListHead!=NULL)
//             {
//                 ringsignCount--;
//                 num = num + pRingListHead->nRingsign*getPowerofTen(ringsignCount);
//                 pRingListTemp = pRingListHead;
//                 pRingListHead=pRingListHead->pNext;
//                 delete pRingListTemp;
//             }
//             num+=1.0;
//             ringsignCount=0;
//             pRingListHead = convertNumberToList(num);
//             pRingListTemp = pRingListHead;
//             while(pRingListTemp->pNext!=NULL)
//             {
//                 ringsignCount++;
//                 pRingListTemp=pRingListTemp->pNext;
//             }
//             ringsignCount++;
//             pRingListTail=pRingListTemp;
//             pRingListTemp=NULL;
        }
        else if (eventCode == 8)  //Galadriel Queen
        {
            if (theKnight.HP == maxHP) continue;
            theKnight.HP = maxHP;
            if (isIsildur || isLegolas) continue;
            if (ringsignCount == 1)
            {
                pRingListTail = NULL;
                delete pRingListHead;
                pRingListHead = NULL;
                return NULL;
            }
            ringsignCount--;
            pRingListTemp = pRingListHead;
            while(pRingListTemp->pNext != pRingListTail)
            {
                pRingListTemp = pRingListTemp->pNext;
            }
            pRingListTemp->pNext = NULL;
            delete pRingListTail;
            pRingListTail= pRingListTemp;
            pRingListTemp = NULL;
        }
        else
        {
            b = eventOrder%10;
            levelO = eventOrder>6 ? (b>5?b:5) : b;
            ringsignO = eventCode%10;
            opponentType = eventCode/10;
            if (isLegolas && (opponentType==3 || opponentType==6) ) //A5 Question
            {
                continue;
            }
            else if (isGandalf && (opponentType == 1 || opponentType==2 || opponentType==6)) //A6 Question
            {
                continue;
            }
            if (theKnight.level > levelO)  //Win
            {
                ringsignCount++;
                if (opponentType==9)  //A3 Question
                {
                    if(ringsignCount==1)
                    {
                        continue;
                    }
                    else
                    {
                        pRingListTail = pRingListHead;
//                         ringsignList* pRingListPre = pRingListHead;
//                         pRingListTemp = pRingListHead->pNext;
//                         ringsignList* pRingListPost = pRingListTemp;
//                         pRingListPre->pNext = NULL;
//                         while(pRingListTemp!=NULL)
//                         {
//                             pRingListPost=pRingListPost->pNext;
//                             pRingListTemp->pNext = pRingListPre;
//                             pRingListPre=pRingListTemp;
//                             pRingListTemp=pRingListPost;
//                         }
                        pRingListHead = reverseList(pRingListHead);
                    }
                }
                else
                {
                    pRingListTail = insertRingsign(pRingListTail, ringsignO);
                }
            }
            else if (theKnight.level < levelO) //Lose
            {
                damage = getBaseDamage(opponentType)*levelO;
                theKnight.HP = theKnight.HP - damage;
                if (isIsildur) continue;
                if (opponentType==4) //A1 Question
                {
                    pRingListTail=NULL;
                    pRingListTemp = pRingListHead;
                    ringsignList* pRingsignDel = NULL;
                    while(pRingListTemp!=NULL)
                    {
                        if(pRingListTemp->nRingsign==ringsignO)
                            pRingsignDel = pRingListTemp;
                        pRingListTemp = pRingListTemp->pNext;
                    }
                    if(pRingsignDel!=NULL)
                    {
                        ringsignCount--;
                        if(pRingsignDel == pRingListHead)
                        {
                            pRingListHead=pRingListHead->pNext;
                            delete pRingsignDel;
                        }
                        else
                        {
                            ringsignList* pRingListPre = pRingListHead;
                            while(pRingListPre->pNext != pRingsignDel)
                            {
                                pRingListPre= pRingListPre->pNext;
                            }
                            pRingListPre->pNext = pRingsignDel->pNext;
                            pRingsignDel->pNext = NULL;
                            delete pRingsignDel;
                            pRingsignDel = NULL;
                        }
                        pRingListTail = getLastPointer(pRingListHead);
                    }
                }
                else if (opponentType==5) //A2 Question
                {
                    if (ringsignCount<=3)
                    {
                        pRingListTail=NULL;
                        while(pRingListHead != NULL){
                            pRingListTemp = pRingListHead;
                            pRingListHead = pRingListHead->pNext;
                            delete pRingListTemp;
                            return NULL;
                        }
                    }
                    else
                    {
                        int count = 0;
                        while (count<3)
                        {
                            pRingListTemp=pRingListHead;
                            pRingListHead = pRingListHead->pNext;
                            delete pRingListTemp;
                            count++;
                        }
                        pRingListTemp = NULL;
                        ringsignCount-=3;
                    }
                }
                else if (opponentType==9)  //A3
                {
                    pRingListTemp = pRingListHead;
                    pRingListTail = NULL;
                    pRingListHead = insertRingsign(NULL,-1);
                    pRingListTail = pRingListHead;
                    ringsignCount = 0;
                    ringsignList* q;
                    while(pRingListTemp!=NULL)
                    {
                        if(pRingListTemp->nRingsign != ringsignO)
                        {
                            ringsignCount++;
                            pRingListTail = insertRingsign(pRingListTail,pRingListTemp->nRingsign);
                        }
                        q = pRingListTemp;
                        pRingListTemp = pRingListTemp->pNext;
                        delete q;
                    }
                    pRingListTemp = pRingListHead;
                    pRingListHead = pRingListHead->pNext;
                    delete pRingListTemp;
                    pRingListTemp= NULL;
                }
                if (theKnight.HP <= 0)
                {
                    pRingListTail=NULL;
                    pRingListTemp=pRingListHead;
                    while(pRingListHead != NULL){
                        pRingListTemp = pRingListHead;
                        pRingListHead = pRingListHead->pNext;
                        delete pRingListTemp;
                    }
                    return NULL;
                }
            }

        }

    }
	return pRingListHead;
}

int checkPalindrome(ringsignList* pRingsign)
{
    if(pRingsign == NULL) return 0;

    ringsignList* pTempHead = pRingsign;
    ringsignList* pTempTail = NULL;
    ringsignList* pTemp = NULL;
    //tim vi tri cuoi cung
    pTemp=pTempHead;
    while(pTemp->pNext!=NULL)
    {
        pTemp = pTemp->pNext;
    }
    pTempTail = pTemp;
    while(true)
    {
        if(pTempHead->nRingsign != pTempTail->nRingsign)
            return 0;
        if(pTempHead == pTempTail)
            return 1;
        pTempHead=pTempHead->pNext;
        if(pTempHead == pTempTail)
            return 1;
        pTemp = pTempHead;
        while(pTemp->pNext!=pTempTail)
        {
            pTemp=pTemp->pNext;
        }
        pTempTail = pTemp;
    }

}
