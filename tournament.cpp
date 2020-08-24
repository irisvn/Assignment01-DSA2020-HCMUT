#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

/* 
Trong đó ringsignList sẽ là một danh sách liên kết chứa các ringsign mà hiệp sĩ có được sau khi kết thúc hành trình, được khai báo như sau:
	struct ringsignList {
		int nRingsign; //ringsign
		ringsignList* pNext;
	}
Thông tin về hiệp sĩ được truyền qua biến tham khảo theKnight thuộc cấu trúc knight được khai báo như sau:
	struct knight {
		int HP;
		int level;
		int nInitRingsign;
	}

Thông số pEvent là một con trỏ trỏ đến danh sách liên kết của các sự kiện được đọc từ file input, được định nghĩa như sau:
	struct evenList {
		int nEvenCode;
		evenList* pNext;
	}
*/

const float monter_uruk_hai = 1;
const float monter_ma_nhan 	= 1.8;
const float monter_strider 	= 4.5;
const float monter_gollum 	= 8.2;
const float monter_lurtz 	= 7.5;
const float monter_gimli 	= 9;
const float monter_saruman 	= 0.1;

const int action[4][9] = {
	{3, 3, 3, 3, 3, 3, 2, 3, 3},
	{1, 1, 1, 1, 1, 1, 2, 1, 1},
	{3, 3, 0, 3, 3, 0, 2, 1, 3},
	{0, 0, 3, 3, 3, 0, 2, 3, 3}
};

int calculateLevelO(int _numberEvent)
{
	int _temp = _numberEvent % 10;
	return _numberEvent > 6 ? ( _temp > 5 ? _temp : 5 ) : _temp;
}

float calculateDamage(int _monter, int _levelO) 
{	
	float _damage;

	switch (_monter)
	{
		case 1:
			_damage = monter_uruk_hai;
			break;
		case 2:
			_damage = monter_ma_nhan;
			break;
		case 3:
			_damage = monter_strider;
			break;
		case 4:
			_damage = monter_gollum;
			break;
		case 5:
			_damage = monter_lurtz;
			break;
		case 6:
			_damage = monter_gimli;
			break;
		case 9:
			_damage = monter_saruman;
			break;
	}

	if (_damage > 0) {
		return (int)(_damage*10*_levelO);
	} else {
		return 0;
	}
}

ringsignList* deleteOneNodeInEC(ringsignList* _head_ringsign, int ringSignO)
{
	ringsignList* _temp_ringsign = new ringsignList, *_prev;
	_temp_ringsign = _head_ringsign;

	// cout << ringSignO << endl;

	if (_temp_ringsign->nRingsign == ringSignO)
	{
		_head_ringsign = _temp_ringsign->pNext;
		delete _temp_ringsign;
		return _head_ringsign;
	}
	

	while( _temp_ringsign != NULL && _temp_ringsign->nRingsign != ringSignO )
	{
		_prev = _temp_ringsign;
		_temp_ringsign = _temp_ringsign->pNext;
	}

	if (_temp_ringsign == NULL) 
	{
		return _head_ringsign;
	}

	_prev->pNext = _temp_ringsign->pNext;
	delete _temp_ringsign;

	return _head_ringsign;
}

ringsignList* reverseEc(ringsignList* _head_ringsign) // Đảo ngược EC
{
	ringsignList* _current_ringsign = new ringsignList;
	_current_ringsign = _head_ringsign;
	ringsignList *pNext = NULL;
	ringsignList *pPrev = NULL;

	while(_current_ringsign != NULL)
	{
		pNext = _current_ringsign->pNext;
		_current_ringsign->pNext = pPrev;
		pPrev = _current_ringsign;
		_current_ringsign = pNext;
	}

	return pPrev;
}

int convertString2Int(string _ec)
{
	return stoi(_ec);
}

string convertInt2String(int _ec)
{
	return to_string(_ec); 
}

string printEc(ringsignList* _head_ringsign)
{
	string _ec;
	while (_head_ringsign != NULL) {
        _ec = _ec + convertInt2String(_head_ringsign->nRingsign);
        _head_ringsign = _head_ringsign->pNext;
    }

	return _ec;
}

// Action gặp quái

ringsignList* arwenChangeEc(ringsignList* _head_ringsign) // Gặp tiên nữ Arwen
{
	ringsignList* _current_ringsign = _head_ringsign;
	ringsignList* _temp_ringsign = new ringsignList;
	int _increase = 1, _sum = 0;

	while(_current_ringsign != NULL) 
	{
		_sum = _increase + _current_ringsign->nRingsign; 
		_increase = (_sum >= 10) ? 1 : 0; 
		_sum = _sum % 10;
		_current_ringsign->nRingsign = _sum;
		_temp_ringsign = _current_ringsign;

		_current_ringsign = _current_ringsign->pNext;
	}

	if (_increase > 0) {
		ringsignList* _new_ringsign = new ringsignList;
		_new_ringsign->nRingsign = _increase;
		_new_ringsign->pNext = NULL;

		_temp_ringsign->pNext = _new_ringsign;
	}

	_head_ringsign = reverseEc(_head_ringsign);
	if (_head_ringsign->nRingsign == 0) 
	{
		_head_ringsign = deleteOneNodeInEC(_head_ringsign, 0);
	}
	_head_ringsign = reverseEc(_head_ringsign);

	return _head_ringsign;
}

ringsignList* galadrielChangeEc(ringsignList* _head_ringsign) // Gặp nữ vương Galadriel
{
	ringsignList* _temp_ringsign = new ringsignList;

	_temp_ringsign = _head_ringsign;
	_head_ringsign = _temp_ringsign->pNext;
	_temp_ringsign->pNext = NULL;
	delete _temp_ringsign;
	return _head_ringsign; 
}

ringsignList* gollumChangeEc(ringsignList* _head_ringsign, int _ringSignO) // Gặp quái vật Gollum
{
	_head_ringsign = deleteOneNodeInEC(_head_ringsign, _ringSignO);
	return _head_ringsign;
}

ringsignList* lurtzChangeEc(ringsignList* _head_ringsign) 
{
	ringsignList* _temp_ringsign = new ringsignList;
	_head_ringsign = reverseEc(_head_ringsign); // Reverse lại EC

	int i = 0;

	while (i < 3 && _head_ringsign != NULL)
	{
		_temp_ringsign = _head_ringsign;
		_head_ringsign = _temp_ringsign->pNext;
		_temp_ringsign->pNext = NULL;
		delete _temp_ringsign;

		i++;
		_head_ringsign->pNext;
	}

	_head_ringsign = reverseEc(_head_ringsign); // Reverse lại EC
	
	return _head_ringsign;
}

ringsignList* sarumanChangeEcWin(ringsignList* _head_ringsign)
{
	_head_ringsign = reverseEc(_head_ringsign); // Reverse lại EC
	return _head_ringsign;
}

ringsignList* sarumanChangeEcLose(ringsignList* _head_ringsign, int ringSignO)
{
	ringsignList* _temp_ringsign = new ringsignList;
	_temp_ringsign = _head_ringsign;

	while(_head_ringsign != NULL && _head_ringsign->nRingsign == ringSignO)
	{
		_temp_ringsign = deleteOneNodeInEC(_temp_ringsign, ringSignO);
		// cout << _head_ringsign->nRingsign << endl;
		
		_head_ringsign = _head_ringsign->pNext;
	}
	return _temp_ringsign;
}

// End Action

ringsignList* combat (knight& theKnight, eventList* pEvent)
{
	int _actionCode;
	int _numberEvent = 0;
	int _currentCode = 0;
	int _firstCode = pEvent->nEventCode;

	bool _isildur = false;
	bool _legolas = false;

	int _maxHp = (&theKnight)->HP;
	int _hp = (&theKnight)->HP;
	int _level = (&theKnight)->level;
	int _ringSign = (&theKnight)->nInitRingsign;

	int _monter = 0;
	int _levelO = 0;
	int _ringSignO = 0;
	int _damageO = 0;

	eventList* _current_event = pEvent;
	ringsignList* _head_ringsign = new ringsignList;
	_head_ringsign->nRingsign = _ringSign;
	_head_ringsign->pNext = NULL;

	if (_firstCode == 0) 
	{
		return _head_ringsign;
	}

	while(_current_event != NULL && _current_event->nEventCode > 0)
	{
		if (_head_ringsign == NULL) 
		{
			break;
		}

		// cout << "================EC: " << printEc(_head_ringsign) << endl;

		_numberEvent++;
		_currentCode = _current_event->nEventCode;

		_monter = (_currentCode > 9) ? (_currentCode/10) : _currentCode;
		_levelO = calculateLevelO(_numberEvent);
		_ringSignO = (_currentCode > 9) ? (_currentCode%10) : 0;

		switch (_maxHp)
		{
			case 777:
				_actionCode = action[1][_monter-1];
				break;
			case 888:
				_actionCode = action[2][_monter-1];
				break;
			case 999:
				_actionCode = action[3][_monter-1];
				break;
			default:
				_actionCode = action[0][_monter-1];
				break;
		}

		// cout << "Hiep si===" << endl;
		// cout << _actionCode << endl;
		// cout << "HP: " << _hp << endl;
		// cout << "Level: " << _level << endl;
		// cout << "Quai vat===" << endl;
		// cout << "STT: " << _monter << endl;
		// cout << "Level: " << _levelO << endl;
		// cout << "Ring: " << _ringSignO << endl;
		

		if (_actionCode == 0) 
		{
			_current_event = _current_event->pNext;
			continue;
		}

		if (_monter == 7) 
		{
			_head_ringsign = arwenChangeEc(_head_ringsign);
			_current_event = _current_event->pNext;
			continue;
		}
		
		if (_monter == 8)
		{
			if (_hp < _maxHp)
			{
				if (_actionCode != 1) {
					_head_ringsign = galadrielChangeEc(_head_ringsign);
				}
				_hp = _maxHp;
			}

			_current_event = _current_event->pNext;
			continue;
		}

		ringsignList* _current_ringsign = new ringsignList;

		if (_level > _levelO) // Chiến thắng - Linked list - Stack
		{	
			if (_monter == 9)
			{
				_head_ringsign = sarumanChangeEcWin(_head_ringsign);
			}
			else
			{
				_current_ringsign->nRingsign = _ringSignO;
				_current_ringsign->pNext = _head_ringsign;
				_head_ringsign = _current_ringsign;
			}
		}
		else if (_level < _levelO)
		{			
			_damageO = calculateDamage(_monter, _levelO);
			_hp = _hp - _damageO;

			// cout << "Combat===" << endl;
			// cout << "Dam: " << _damageO << endl;
			// cout << "Hp con lai: " << _hp << endl;

			if (_hp <= 0)
			{
				break;
			}
			else if (_actionCode != 1)
			{
				switch (_monter)
				{
					case 4:
						_head_ringsign = gollumChangeEc(_head_ringsign, _ringSignO);
						break;
					case 5:
						_head_ringsign = lurtzChangeEc(_head_ringsign);
						break;
					case 9:
						_head_ringsign = sarumanChangeEcLose(_head_ringsign, _ringSignO);
						break;
				}
			}	
		}

		// cout << "==END==========" << endl;

		_current_event = _current_event->pNext;
	}

	// cout << "================EC - End Combat : " << printEc(_head_ringsign) << endl;

	if (_hp > 0)
	{
		(&theKnight)->HP = _hp;

		return reverseEc(_head_ringsign);
	} 
	else 
	{
		(&theKnight)->HP = _hp + _damageO;
		return NULL;
	}
}

int checkPalindrome(ringsignList* pRingsign)
{
	if (pRingsign == NULL)
	{
		return 0;
	}

	if (pRingsign->nRingsign >= 0 && pRingsign->pNext == NULL)
	{
		return true;
	}

	return 0;
}
