#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>

using namespace std;

#define WC_DEBUG 0


void FatalError(const char* msg)
{
	cout << msg << endl;
	exit(1);
}

class GameTime 
{
public:
	int hour;
	int minute;
	int totalMinute;
	
	GameTime()
	{
		hour = 0;
		minute = 0;
		totalMinute = 0;
	}
	
	void Step();
	void Print();
	void Clear();
};


// 全局变量
int g_total_city_count = 0; // 城市总数
int g_loyalty_decrement = 0; // 忠诚度减少数
vector<class City*> g_city_vector; // 所有城市
GameTime g_time;  // 全局时间
int g_arrow_atk;  // arrow攻击力
int g_max_id;     // 全局ID
int g_red_battle_life; // red胜利
int g_blue_battle_life; // blue胜利

void PrintNewLine() {
	// cout << "\n";
	// cout << endl; // endl 写入换行符并且刷新 
	
	static int n = 0;
	if (n!=0) {
		// printf("\n"); 
		cout << endl; // cout 是有缓冲区的输出 
	}
	n++;
	
}


// 据说cout输出不行 
#define USE_PRINTF 1 

#define WARRIOR_FOREACH_START(warriorMap)	for (map<int, Warrior*>::iterator it = warriorMap.begin();it != warriorMap.end(); it++) {
#define WARRIOR_FOREACH_END() }


void PrintTime(GameTime& time) {
	
	printf("%03d:%02d ", time.hour, time.minute);

    // printf("%d ", time);
}

void GameTime::Print()
{
	PrintTime(*this);
}

void GameTime::Clear()
{
	hour = 0;
	minute = 0;
	totalMinute = 0;
}

void GameTime::Step()
{
	minute += 1;
	totalMinute ++;
	if (minute >= 60) {
		minute = 0;
		hour += 1;
	}
	// cout << hour << ":" << minute << endl;
}

class City
{
public:
	int life;
	int number;
	string flag; // 旗帜
	string curWinner;  // 当前胜利方
	string prevWinner; // 上一轮胜利方,如果是平局则是tie
	map<int, class Warrior*> warriorMap;  // <编号, 武士>
	// vector<Weapon> weapons; // 战斗死亡留下的武器
	
	City();
	~City();
	void BattleEnded(); // 战斗结束，判断flag
	virtual void Step(GameTime& time);    // 制造生命元
	virtual void AddWarrior(class Warrior*w);
	virtual void RemoveWarrior(class Warrior* w);
	virtual void Introduce();
	virtual bool IsHead();
	virtual int  GetWarriorCount();
	virtual int  GetAliveWarriorCount();
	Warrior* GetWarrior(const string& group);
	string GetFullName();
};

// 武器
class Weapon
{
public:
	int number;
	string name;
	int atk;
	
	public:
		Weapon()
		{
			name = "none";
			atk = 0;
		}
		
		Weapon(string name, int number)
		{
			this->name = name;
			this->number = number;
			// this->atk = atk;
		}
		~Weapon()
		{
			
		} 
		
		string GetName()
		{
			return name;
		}
		
		void Weaken(); // 使用之后削弱
};


class WeaponFactory
{
	private:
		Weapon sword;
		Weapon bomb;
		Weapon arrow;
		
	public:
		WeaponFactory()
		{
			sword = Weapon("sword", 0);
			bomb  = Weapon("bomb", 1);
			arrow = Weapon("arrow", 2);
		}
		
		static Weapon makeWeapon(int number)
		{
			number = number % 3;
			if (number == 0) {
				return Weapon("sword", 0);
			} else if (number == 1) {
				return Weapon("bomb", 1);
				// return bomb;
			} else if (number == 2) {
				return Weapon("arrow", 2);
				// return arrow;
			}
		}	
};

class Warrior
{
public:

	// char[] 没有定义拷贝函数 
    string name; 
    char time[5];
	int id;       // 全局唯一的ID
    int number;
    int atk;      // 攻击力 
    int life; // 生命值 
	int transferedLife;
    int loyalty;  // 忠诚度 
    double morale; // 士气 
    int count;
	int targetRange; // 距离敌军距离
    string group;
	string enemy;
    class HeadQuarter* head;
	class City* city;
	int killed;
	bool requireAward;
	Weapon weapon;
	Weapon arrow; // 每个士兵都能有箭
	int arrowCount;
	Weapon bomb;  // 或者炸弹
	int bombCount;
	bool reached = false;

    Warrior () {
		count = 0;
		killed = 0;
		requireAward = false;
		city = NULL;
		life = 0;
		transferedLife = 0;
		arrowCount = 0;
		bombCount = 0;
		// cout << "ID=" << id << endl;
    }

    Warrior(const char* name) {
        this->name = name;
        count = 0;
		killed = 0;
		requireAward = false;
		city = NULL;
		life = 0;
		transferedLife = 0;
		arrowCount = 0;
		bombCount = 0;
    }

    virtual ~Warrior() {
    	#if WC_DEBUG
		cout << "Warrior destructor called" << endl;
		#endif
    }
    
    void SetLife(int life)
    {
    	this->life = life;
	}

    Warrior* CreateNew() {
    	count += 1;
        Warrior* newWarrior = this->Clone();
		newWarrior->ComputeEnemy();
		newWarrior->id = g_max_id;
		g_max_id++;
        return newWarrior;
    }

    void SetNumber(int number) {
        this->number = number;
    }
	
	void Born(GameTime time, int count);
    virtual void ExtraOutput(); 
    
    virtual void Attack(Warrior* enemy, bool atkBack=false);   // atkBack 是否是反击
	virtual void Yell() {} // 欢呼
    virtual void AttackBack(Warrior* enemy);
	virtual void PostAttack(Warrior* enemy); // 攻击之后的动作
	virtual void Attacked(int damage);
	virtual void Awarded();
    virtual void Die();
    virtual int  GetWeaponAtk();
	virtual void CheckArrow();
	virtual void CheckBomb();
	virtual bool CheckRunAway(); // 检查是否逃跑
	virtual void March(); // 前进
	virtual void ReportPosition(); 
	virtual void Introduce(); // 自我介绍
	virtual int  GetEnemyRange(); 
	
	bool IsInEnemyCenter(); // 根据所在城市编号判断
	bool IsDead();
	bool IsAttackFirst();
	
    void PrintGroupAndName(); 
	string GetFullName();
	virtual void CheckCityLife();
	virtual void ReportCityLife();
	virtual void TakeWeapon(Weapon& weapon);
	virtual void ReportWeapon();
	virtual void TransferLife(Warrior* enemy) {} // 转移life
	virtual void Killed();
	
	virtual int GetAtk(bool fightBack = false);
	void ComputeEnemy();
	
    virtual Warrior* Clone()
    {
    	Warrior *w = new Warrior;
		*w = *this;
    	w->name = name;
		w->number = number;
		w->atk = atk;
		w->morale = morale;
		w->city = city;
		w->count = count;
    	return w;
	}
};


class Dragon : public Warrior 
{
	private:
		int m_armCount;
		
		Weapon m_weapon;
		
	public:
		
		Dragon()
		{
			name = "dragon";
			m_armCount = 0;
		}
		
		virtual ~Dragon()
		{
			#if WC_DEBUG
			cout << "Dragon destructor called" << endl;
			#endif
		}
		
		virtual Warrior* Clone()
		{
			#if WC_DEBUG
			cout << "Dragon Clone Called!" << endl;
			#endif
			Dragon* d = new Dragon;
			*d = *this;
			return d;
		}
		
		void ExtraOutput();
		virtual void Yell();
		virtual void PostAttack(Warrior* enemy);
}; 

class Lion : public Warrior
{

public:
	int prevLife;
	
	Lion()
	{
		name = "lion";
		loyalty = 0;
	}
	
	virtual Warrior* Clone()
	{
		Lion* temp = new Lion;
		*temp = *this;
		return temp; 
	} 
	
	void ExtraOutput();
	virtual void Attacked(int atk);
	virtual bool CheckRunAway();
	virtual void PostAttack(Warrior* enemy);
	virtual void TransferLife(Warrior* enemy);
};

class Iceman : public Warrior
{

public:

	int marchCount;
	
	Iceman()
	{
		marchCount = 0;
		name = "iceman";
	}
	
	virtual Warrior* Clone()
	{
		Iceman* temp = new Iceman;
		*temp = *this;
		return temp; 
	} 
	
	void ExtraOutput();
	virtual void March();
};

void Iceman::ExtraOutput()
{
	Weapon weapon = WeaponFactory::makeWeapon(number);
	TakeWeapon(weapon);
	// cout << "It has a " << weapon.GetName() << endl;
}

class Ninja: public Warrior
{

public:
	
	Ninja()
	{
		name = "ninja";
	}
	
	virtual Warrior* Clone()
	{
		Ninja* temp = new Ninja;
		*temp = *this;
		return temp; 
	} 
	
	void ExtraOutput();
	virtual void AttackBack(Warrior* enemy);
	virtual int  GetAtk(bool atkBack=false);
	
};

void Ninja::ExtraOutput()
{
	Weapon w1 = WeaponFactory::makeWeapon(number);
	Weapon w2 = WeaponFactory::makeWeapon(number+1);
	TakeWeapon(w1);
	TakeWeapon(w2);
	// cout << "It has a " << w1.GetName() << " and a " << w2.GetName() << endl;
}

void Ninja::AttackBack(Warrior* enemy)
{
	// Ninja不反击
}

int Ninja::GetAtk(bool atkBack)
{
	if (atkBack)
	{
		return 0;
	}
	return atk + weapon.atk;
}

class Wolf: public Warrior
{

public:
	
	Wolf()
	{
		name = "wolf";
	}
	
	virtual Warrior* Clone()
	{
		Wolf* wolf = new Wolf;
		*wolf = *this;
		return wolf; 
	} 
	
	void ExtraOutput();
	virtual void PostAttack(Warrior* enemy);
	
};

void Wolf::ExtraOutput()
{
	
}

class HeadQuarter : public City
{
public:

    string name;
    int totalLife;
    int life;
    int minWarriorLife;
    int awardPrize;    // 杀死敌人的奖励 
    vector<Warrior*> warriorPrototype;
	vector<int> warriorCountVector;
	map<int, Warrior*> allWarrior;
	
    int warriorIndex;
    int warriorNumber;
    char time[5];
    bool stoped;

    HeadQuarter(const char* name) {
		this->name = name;
        this->warriorIndex = 0;
        this->minWarriorLife = -1;
        this->warriorIndex = 0;
        this->warriorNumber = 0;
        this->stoped = false;
        this->awardPrize = 8;
    }
    ~HeadQuarter() {
		for(vector<Warrior*>::iterator it = warriorPrototype.begin(); it != warriorPrototype.end(); it++)
		{
			delete *it;
		}
    }
    
    HeadQuarter& operator=(int totalLife) {
        this->totalLife = totalLife;
        this->life = totalLife;
        return *this;
    }

    void MakeWarrior(GameTime &time);
    Warrior* GetNextWarrior();
    void AddWarriorPrototype(Warrior *w);
    bool NotStop();
    int GetRemain();
    virtual void Award(Warrior* w);
	virtual void AwardAll();
	virtual void _Step(GameTime&time, Warrior* w);
	virtual void Step(GameTime& time);
	virtual void DestroyWarrior(Warrior*w);
	virtual bool IsHead();
	void ReportLife();
	void CheckTaken(); // 检查有没有被占领
};

void HeadQuarter::CheckTaken()
{
	if (GetWarriorCount() >= 2)
	{
		stoped = true;
		g_time.Print();
		cout << name << " headquarter was taken" << endl;
		return;
	}
}

bool HeadQuarter::IsHead()
{
	return true;
}

int HeadQuarter::GetRemain()
{
	return this->life;
}

void HeadQuarter::Award(Warrior* w)
{
	int award = 8; 
	if (this->life >= award)
	{
		// cout << "Award " << w->GetFullName() << endl;
		this->life -= award;
		w->life += award;
		// g_time.Print();
	}
	w->requireAward = false;
}

void HeadQuarter::AwardAll()
{
	vector<Warrior*> sorted;
	for (map<int, Warrior*>::iterator it = allWarrior.begin(); 
		it != allWarrior.end(); it++)
	{
		Warrior* w = it->second;
		if (w->requireAward)
		{
			sorted.push_back(w);
		}
	}
	// award the soldiers who killed enemies;
	for (vector<Warrior*>::iterator it = sorted.begin(); 
		it != sorted.end(); it++)
	{
		Award(*it);
	}
}

Warrior* HeadQuarter::GetNextWarrior() {
    int i = 0;
    for (i = 0; i < warriorPrototype.size(); i++) {
        warriorIndex = warriorIndex % warriorPrototype.size();
        Warrior *w = warriorPrototype[warriorIndex];
		if (w->life > life)
		{
			// 造不起
			return NULL;
		}
        warriorIndex += 1;
        if (w->life <= this->life) {
        	// w.count += 1;
			this->life -= w->life;
			// cout << GetFullName() << ", cost " << w->life << endl;
            return w->CreateNew();
        }
    }
    return NULL;
}

void Wolf::PostAttack(Warrior* enemy)
{
	if (enemy->IsDead())
	{
		if (weapon.atk <=0)
		{
			weapon = enemy->weapon;
		}
		
		if (arrowCount <= 0)
		{
			arrowCount += enemy->arrowCount;
		}
		
		if (enemy->bombCount > 0)
		{
			bombCount = 1;
		}
	}
}

void Dragon::Yell()
{
	if (!IsDead() && morale >= 0.8)
	{
		g_time.Print();
		cout << GetFullName() << " yelled in " 
			<< city->GetFullName() 
			<< endl;
	}
}

void Dragon::PostAttack(Warrior* enemy)
{
	if (IsDead())
	{
		return;
	}
	if (enemy->IsDead())
	{
		morale += 0.2;
	}
	else
	{
		morale -= 0.2;
	}
}

void Lion::Attacked(int atk)
{
	if (IsDead())
	{
		// 已经死了保持之前的生命值
		return;
	}
	prevLife = life;
	Warrior::Attacked(atk);
}

void Lion::PostAttack(Warrior* enemy)
{
	if (!enemy->IsDead())
	{
		// 忠诚度减少
		loyalty-=g_loyalty_decrement;
		if (IsDead())
		{
			enemy->life += prevLife;
			prevLife = 0;
		}
	} 
}

void Lion::TransferLife(Warrior* enemy)
{
	if (enemy->IsDead())
	{
		// 敌人也死了，没法转移了
		prevLife = 0;
		return;
	}
	if (IsDead())
	{
		enemy->transferedLife = 0;
		prevLife = 0;
	}
}

void Iceman::March()
{
	Warrior::March();
	marchCount++;
	if (marchCount >= 2)
	{
		atk += 20;
		life -= 9;
		if (life <= 0)
		{
			life = 1;
		}
		marchCount = 0;
	}
}

void HeadQuarter::MakeWarrior(GameTime &time) {
    Warrior* w = GetNextWarrior();
    if (w == NULL) {
		
		/*
        if (!stoped) {
            PrintTime(time);
            cout << name << " headquarter stops making warriors" << endl;
            // printf("%s headquarter stops making warriors\n", name);
            // PrintNewLine();
            stoped = true;
        }
		*/
		
        return;
    }
    warriorNumber += 1;
    w->SetNumber(warriorNumber);
    w->Born(time, w->count);
    // delete w;
	AddWarrior(w);
	allWarrior[w->number] = w;
}

bool HeadQuarter::NotStop() {
    // if (stoped) {
    //     return false;
    // }
    // return this->life >= minWarriorLife;
    return !stoped;
}

void HeadQuarter::AddWarriorPrototype(Warrior* w) {
    if (minWarriorLife < 0) {
        minWarriorLife = w->life;
    } else if (w->life < minWarriorLife) {
        minWarriorLife = w->life;
    }
    w->group = this->name;
    w->head = this;
	w->city = this;
    warriorPrototype.push_back(w);
	// w->Introduce();
}

void City::AddWarrior(Warrior* w)
{
	warriorMap[w->id] = w;
}

void City::RemoveWarrior(Warrior* _w)
{
	// Warrior* w = warriorMap[_w->number];
	warriorMap.erase(_w->id);
	// delete w;
}

void HeadQuarter::DestroyWarrior(Warrior* w)
{
	w->city->RemoveWarrior(w);
	RemoveWarrior(w);
	allWarrior.erase(w->number);
	delete w;
}

void HeadQuarter::ReportLife()
{
	g_time.Print();
	cout << life << " elements in " << name << " headquarter" << endl;
}

void HeadQuarter::_Step(GameTime& time, Warrior* w)
{
	int minute = time.minute;
	if (5 == minute)
	{
		// cout << it->first << "==>" << it->second->name << endl;
		w->CheckRunAway();
	}
	else if (10 == minute)
	{
		// 前进
		w->March();
	}
	else if (20 == minute)
	{
		// @see GameWorld
		// 制造生命元
		// 司令部不造生命元
		// this->life += 10;
		// 这个过程是全局的
	}
	else if (30 == minute)
	{
		// 如果只有一个武士，取走生命元
		// w->CheckCityLife();
	}
	else if (35 == minute)
	{
		// 武士放箭
		// w->CheckArrow();
	}
	else if (38 == minute)
	{
		// 武士使用bomb
		// w->CheckBomb();
	}
	else if (40 == minute)
	{
		// @see GameWorld
		// 战斗发生在全局
		// 武士战斗
		// 如果敌人在5分钟前已经被飞来的arrow射死，
		// 那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利
	}
	else if (55 == minute)
	{
		// 武士报告武器情况
		// ReportWeapon();
		w->ReportWeapon();
	}
	
}

void HeadQuarter::Step(GameTime& time)
{
	int minute = time.minute;
	// 判断有没有被占领
	if (stoped)
	{
		return;
	}

	// 0分 战士出生
	if (0 == minute)
	{
		MakeWarrior(time);
		return;
	}
	else if (50 == minute)
	{
		// 司令部报告生命元数量
		ReportLife();
		return;
	}
	
	map<int, Warrior*> copy = allWarrior;

	if (name == "red")
	{
		map<int, Warrior*>::reverse_iterator rit;
		for (rit = copy.rbegin(); rit != copy.rend(); rit++)
		{
			Warrior* w = rit->second;
			_Step(time, w);
		}
	}
	else
	{
		map<int, Warrior*>::iterator it;
		for (it = copy.begin(); it != copy.end(); it++)
		{
			Warrior* w = it->second;
			_Step(time, w);
		}
	}
}

void Warrior::Born(GameTime time, int count) {
	// PrintNewLine(); 
    PrintTime(time);
    
	/*
    cout << group << " " << name << " " << number 
        << " born with strength " << life << "," << count << " " 
        << name << " in " << group << " headquarter" << endl;
    */
	
	cout << group << " " << name << " " << number << " born" << endl;
    
    ExtraOutput();
}

int Warrior::GetWeaponAtk()
{
	return weapon.atk;
}

void Warrior::Attack(Warrior* enemy, bool atkBack)
{
	requireAward = false;
	// 双方可能射箭同时杀死对方, 在CheckArrow里面，不算战斗
	if (life <= 0)
	{
		// this unit is dead
		return ;
	}
	
	// 判断敌人有没有死亡
	if (enemy->life <= 0)
	{
		killed += 1;
		// requireAward = true;
		return;
	}
	int atk = GetAtk(atkBack);
	
	g_time.Print();
	cout << GetFullName() << " attacked "
		<< enemy->GetFullName()
		<< " in " << city->GetFullName()
		<< " with " << life << " elements and force " << this->atk
		<< endl;
	
	weapon.Weaken();
	enemy->Attacked(atk);
	if (enemy->life <= 0)
	{
		enemy->Killed();
		// enemy is dead 
		// head->Award(this);
		// head->RemoveWarrior(enemy);
		// award the soldier after all battle
		killed += 1;
		// requireAward = true;
	}
}

void Warrior::PostAttack(Warrior* enemy)
{
	// do nothing;
}

void Warrior::AttackBack(Warrior* enemy)
{
	if (IsDead() || enemy->IsDead())
	{
		return;
	}
	int atk = GetAtk(true);
	weapon.Weaken(); // 武器变钝
	enemy->Attacked(atk);
	
	// fight back
	g_time.Print();
	cout << GetFullName()
		<< " fought back against "
		<< enemy->GetFullName()
		<< " in "
		<< city->GetFullName()
		<< endl;
	
	if (enemy->IsDead())
	{
		enemy->Killed();
		killed += 1;
		// requireAward = true;
	}
}

void Warrior::CheckArrow()
{
	// 死了也可以
	if (arrowCount <= 0)
	{
		return;
	}
	int nextCityNum;
	string enemyGroup;
	// check arrow
	if (group == "red")
	{
		enemyGroup = "blue";
		nextCityNum = city->number+1;
		if (nextCityNum >= g_city_vector.size()-1)
		{
			return;
		}
	} else if (group == "blue")
	{
		enemyGroup = "red";
		nextCityNum = city->number-1;
		if (nextCityNum < 1)
		{
			return;
		}
	} else {
		cout << "fatal error" << endl;
		exit(1);
	}
	City* nextCity = g_city_vector[nextCityNum];
	Warrior* w = nextCity->GetWarrior(enemyGroup);
	if (w != NULL)
	{
		if (w->IsDead())
		{
			return;
		}
		w->Attacked(g_arrow_atk);
		arrowCount--;
		
		g_time.Print();
		PrintGroupAndName();
		
		if (w->IsDead())
		{
			cout << "shot and killed " << w->GetFullName() << endl;
			w->TransferLife(this);
		}
		else
		{
			cout << "shot" << endl;
		}
		return;
	}
}

int Warrior::GetAtk(bool fightBack)
{
	if (fightBack)
	{
		return atk / 2 + weapon.atk;
	}
	else 
	{
		return atk + weapon.atk;
	}
}

void Warrior::CheckBomb()
{
	if (IsDead())
	{
		return;
	}
	if (bombCount == 0)
	{
		return;
	}
	if (city->GetWarriorCount() == 2)
	{
		// 这样才可以Fight
		Warrior * w = city->GetWarrior(enemy);
		
		if (w->IsDead())
		{
			return;
		}
		
		int eAtk;
		// 如果自己先攻击
		if (IsAttackFirst())
		{
			if (GetAtk() >= w->life)
			{
				// 能把敌人杀死
				return;
			}
			eAtk = w->GetAtk(true);
		}
		else
		{
			eAtk = w->GetAtk(false);
		}
		
		if (eAtk >= life) {
			// 放炸弹
			w->life = 0;
			this->life = 0;
			w->TransferLife(this);// 
			g_time.Print();
			cout << GetFullName() << " used a bomb and killed " 
				<< w->GetFullName() << endl;
		}
		return;
	}
}

bool Warrior::CheckRunAway()
{
	return false;
}

void Warrior::Attacked(int damage)
{
	this->life -= damage;
}

void Warrior::Awarded()
{
	// this->head->Award(this);
}

bool Warrior::IsDead()
{
	return life <= 0;
}

bool Warrior::IsAttackFirst()
{
	// 在插红旗的城市，以及编号为奇数的无旗城市，由红武士主动发起进攻。
	// 在插蓝旗的城市，以及编号为偶数的无旗城市，由蓝武士主动发起进攻。
	if (group == "red")
	{
		return city->flag == "red" || 
			(city->flag=="tie" && city->number % 2 == 1);
	}
	else if (group == "blue")
	{
		return city->flag == "blue" ||
			(city->flag == "tie" && city->number % 2 == 0);
	}
}

void Warrior::Die()
{
	// 从军营中移除
	this->head->DestroyWarrior(this);
}

void Warrior::Killed()
{
	g_time.Print();
	cout << GetFullName() << " was killed in " << city->GetFullName() << endl;
}

void Warrior::ExtraOutput()
{
	
}

void Warrior::PrintGroupAndName()
{
	cout << group << " " << name << " " << number << " ";
}

string Warrior::GetFullName()
{
	char buf[200];
	sprintf(buf, "%s %s %d", group.c_str(), name.c_str(), number);
	return buf;
}

void Warrior::ReportPosition()
{
	if (reached)
	{
		// 无所事事
		return;
	}
	g_time.Print();
	PrintGroupAndName();
	if (IsInEnemyCenter())
	{
		string enemyGroup;
		if (group == "red")
		{
			enemyGroup = "blue";
		} else if (group == "blue")
		{
			enemyGroup = "red";
		}
		cout << "reached " << enemyGroup << " headquarter with "
			 << life << " elements and force " 
			 << atk << endl;
		reached = true;
	}
	else
	{
		cout << "marched to city " << city->number 
			 << " with " << life << " elements and force " 
			 << atk << endl;
	}
	// 捡起转移的生命值
	life += transferedLife;
	transferedLife = 0;
}

void Warrior::March()
{
	// cout << "I am at city "<< city->number << endl;
	if (IsInEnemyCenter())
	{
		return;
	}
	
	// 离开旧城市
	city->RemoveWarrior(this);
	if (group == "red")
	{
		// 红魔军
		city = g_city_vector[city->number+1];
	} else if (group == "blue")
	{
		// 蓝魔军
		city = g_city_vector[city->number-1];
	}
	else 
	{
		cout << "Warrior::March fatal error" << endl;
	}
	
	// 抵达新城市
	city->AddWarrior(this);
	
	/*
	if (IsInEnemyCenter())
	{
		ReportPosition();
	}
	*/
	// ReportPosition();
}

void Warrior::Introduce()
{
	cout << name << ", life=" << life 
		 << ",loyalty=" << loyalty 
		 << ",atk=" << atk
		 << endl;
}

bool Warrior::IsInEnemyCenter()
{
	// 红魔军的司令部算作编号为0的城市
	// 蓝魔军的司令部算作编号为N+1的城市
	// cout << "IsInEnemyCenter:1" << endl;
	if (group == "red")
	{
		return city->number == g_total_city_count + 1;
	}
	else if (group == "blue")
	{
		return city->number == 0;
	}
	else
	{
		cout << "fatal error" << endl;
		return false;
	}
}

void Warrior::CheckCityLife()
{
	if (IsDead())
	{
		return;
	}
	if (city->GetAliveWarriorCount() == 1 && !city->IsHead())
	{
		// 取走生命元
		int earnedLife = city->life;
		if (earnedLife <= 0)
		{
			// 没有生命元
			return;
		}
		head->life += earnedLife; // 增加生命元
		city->life = 0;
		
		g_time.Print();
		PrintGroupAndName();
		cout << "earned " << earnedLife 
			<< " elements for his headquarter" 
			// << " at " << city->GetFullName()
			<< endl;
	}
}

void Warrior::ReportCityLife()
{
	if (IsDead())
	{
		return;
	}
	// 已经确认胜利
	// 取走生命元
	int earnedLife = city->life;
	if (earnedLife <= 0)
	{
		// 没有生命元
		return;
	}
	
	g_time.Print();
	PrintGroupAndName();
	cout << "earned " << earnedLife 
		<< " elements for his headquarter" 
		// << " at " << city->GetFullName()
		<< endl;
}

void Warrior::TakeWeapon(Weapon& weapon)
{
	if (weapon.name == "arrow")
	{
		arrowCount+=3;
	} else if (weapon.name == "bomb") 
	{
		bombCount++;
	} else {
		// sword
		this->weapon = weapon;
		this->weapon.atk = atk * 0.2;
		// cout << "atk=" << atk << ",sword.atk=" << weapon.atk << endl;
	}
}

void Warrior::ReportWeapon()
{
	if (IsDead())
	{
		return;
	}
	g_time.Print();
	// arrow, bomb, sowrd
	PrintGroupAndName();
	
	if (arrowCount == 0 && bombCount == 0 && weapon.atk==0)
	{
		cout << "has no weapon" << endl;
	}
	else {
		cout << "has ";
		bool comma = false;
		if (arrowCount > 0)
		{
			cout << "arrow(" << arrowCount << ")";
			comma = true;
		}
		if (bombCount > 0)
		{
			if (comma) cout << ",";
			cout << "bomb";
			comma = true;
		}
		if (weapon.atk > 0)
		{
			if (comma) cout << ",";
			cout << "sword(" << weapon.atk << ")";
		}
		cout << endl;
	}
}

void Warrior::ComputeEnemy()
{
	if (group == "blue")
	{
		enemy = "red";
	} else if (group == "red")
	{
		enemy = "blue";
	}
	else
	{
		FatalError("ComputeEnemy");
	}
}

int Warrior::GetEnemyRange()
{
	if (group=="red")
	{
		return g_total_city_count+1 - city->number;
	}
	else if (group == "blue")
	{
		return city->number;
	}
}

void Dragon::ExtraOutput() {
	Weapon weapon = WeaponFactory::makeWeapon(number);
	morale = (double) head->GetRemain() / (double) this->life;
	char buf[20];
	sprintf(buf, "%.2f", morale);
	TakeWeapon(weapon);
	// cout << "It has a " << weapon.GetName() << ",and it's morale is " << buf << endl;
	cout << "Its morale is " << buf << endl;
}

bool Lion::CheckRunAway()
{
	// cout << "Lion::CheckRunAway:1" << endl;
	if (IsInEnemyCenter())
	{
		// 已经到达敌军司令部
		return false;
	}
	// cout << "Lion::CheckRunAway:2" << endl;
	if (loyalty <= 0)
	{
		g_time.Print();
		cout << group << " lion " << number << " ran away" << endl;
		city->RemoveWarrior(this); 
		head->DestroyWarrior(this); // 遍历过程中不能移除
		// cout << "Lion::CheckRunAway:3" << endl;
		return true;
	}
	// cout << "Lion::CheckRunAway:4" << endl;
	return false;
}

void Lion::ExtraOutput()
{
	loyalty = head->GetRemain();
	cout << "Its loyalty is " << loyalty << endl;
}

City::City()
{
	life = 0;
	flag="tie";
	prevWinner = "tie";
	curWinner = "tie";
}

City::~City()
{
	//
}

void City::BattleEnded()
{
	if (curWinner == prevWinner && curWinner != "tie")
	{
		flag = curWinner;
	}
}

void City::Step(GameTime& time)
{
}

void City::Introduce()
{
	cout << "city:" << number
		<< ",[";
		
	for (map<int,Warrior*>::iterator it = warriorMap.begin(); it != warriorMap.end(); it++)
	{
		Warrior* w = it->second;
		w->PrintGroupAndName();
	}
	
	cout << "]" << endl;
}

bool City::IsHead()
{
	return false;
}

int City::GetWarriorCount()
{
	return warriorMap.size();
}

int City::GetAliveWarriorCount()
{
	int count = 0;
	map<int,Warrior*>::iterator it;
	for(it = warriorMap.begin(); it!=warriorMap.end(); it++)
	{
		Warrior* w = it->second;
		if (!w->IsDead())
		{
			count++;
		}
	}
	return count;
}

Warrior* City::GetWarrior(const string& group)
{
	for (map<int,Warrior*>::iterator it = warriorMap.begin(); it != warriorMap.end(); it++)
	{
		Warrior* w = it->second;
		if (w->group == group)
		{
			return w;
		}
	}
	return NULL;
}

string City::GetFullName()
{
	char buf[128];
	sprintf(buf, "city %d", number);
	return buf;
}

class InputGroup {
public:
    int totalLife;
    int cityCount;
    int arrowDamage;
    int loyaltyDec; // Lion的忠诚度减少值 
    int totalTime;  // 总时间 
    int dragon_life;
    int ninja_life;
    int iceman_life;
    int lion_life;
    int wolf_life;
    
    int dragon_atk;
    int ninja_atk;
    int iceman_atk;
    int lion_atk;
    int wolf_atk;
};


class GameWorld
{
	
public:

	HeadQuarter* red;
	HeadQuarter* blue;

	void InitCities(int count, City* red, City* blue);
	void ReleaseCities();
	void Step(GameTime& time);
	void Fight(City* city, Warrior* redWarrior, Warrior* blueWarrior);
	void ReportHeadWarriors(HeadQuarter* head);
	void ReportHeadWeapons(HeadQuarter* head);
};


void GameWorld::ReleaseCities()
{
	// 释放旧的城市
	if (g_city_vector.size() > 2)
	{
		for (int i = 1; i < g_city_vector.size()-1; i++)
		{
			City* city = g_city_vector[i];
			delete city;
		}
	}
}


void GameWorld::InitCities(int count, City* red, City* blue)
{
	ReleaseCities();
	
	// 从 1-> N;
	g_city_vector.clear();
	g_city_vector.push_back(red);
	for (int i = 0; i < count; i++)
	{
		City* city = new City;
		city->number = i+1;
		g_city_vector.push_back(city);
	}
	g_city_vector.push_back(blue);
}

void GameWorld::Fight(City*city, Warrior* redWarrior, Warrior* blueWarrior)
{
	int oldRedLife = redWarrior->life;
	int oldBlueLife = blueWarrior->life;
	redWarrior->requireAward = false;
	blueWarrior->requireAward = false;
	
	bool noFight = false;
	
	if (redWarrior->IsAttackFirst())
	{
		redWarrior->Attack(blueWarrior);
		// redWarrior->Yell();
		if (!blueWarrior->IsDead())
		{
			blueWarrior->AttackBack(redWarrior);
		}
		redWarrior->Yell();
	}
	else
	{
		blueWarrior->Attack(redWarrior);
		// blueWarrior->Yell();
		if (!redWarrior->IsDead())
		{
			redWarrior->AttackBack(blueWarrior);
		}
		blueWarrior->Yell();
	}
	
	// 攻击完成的后续动作
	redWarrior->PostAttack(blueWarrior);
	blueWarrior->PostAttack(redWarrior);
	
	city->prevWinner = city->curWinner;
	
	if (redWarrior->life <= 0 && blueWarrior->life <= 0)
	{
		// 都战死了
		// city->curWinner = "tie";
		// 放炸弹不算战斗，旗帜不变化
		noFight = true;
		redWarrior->Die();
		blueWarrior->Die();
	}
	else if (redWarrior->life <= 0)
	{
		city->curWinner = "blue";
		blueWarrior->requireAward = true;
		redWarrior->Die();
		blueWarrior->ReportCityLife();
		g_blue_battle_life += city->life;
		city->life = 0;
		
		// blueWarrior->requireAward = true;
	}
	else if (blueWarrior->life <= 0)
	{
		city->curWinner = "red";
		redWarrior->requireAward = true;
		blueWarrior->Die();
		redWarrior->ReportCityLife();
		
		g_red_battle_life += city->life;
		city->life = 0;
		
		// redWarrior->requireAward = true;
	}
	else
	{
		city->curWinner = "tie";
	}
	
	if (!noFight && city->curWinner != "tie" && 
		city->curWinner != city->flag && city->curWinner == city->prevWinner)
	{
		// 更改旗帜
		city->flag = city->curWinner;
		g_time.Print();
		cout << city->flag << " flag raised in "
			<< city->GetFullName()
			<< endl;
	}
}

void GameWorld::ReportHeadWarriors(HeadQuarter* head)
{
	map<int,Warrior*> &mmap = head->warriorMap;
	map<int,Warrior*>::iterator it;
	for(it = mmap.begin(); it!=mmap.end();it++)
	{
		Warrior*w = it->second;
		w->ReportPosition();
	}
}

void GameWorld::ReportHeadWeapons(HeadQuarter* head)
{
	map<int,Warrior*> &mmap = head->warriorMap;
	map<int,Warrior*>::iterator it;
	for(it = mmap.begin(); it!=mmap.end();it++)
	{
		Warrior*w = it->second;
		w->ReportWeapon();
	}
}

void GameWorld::Step(GameTime& time)
{
	int minute = time.minute;
	
	
	if (time.minute == 20)
	{
		for (int i = 1; i < g_city_vector.size()-1; i++)
		{
			City* city = g_city_vector[i];
			city->life += 10;
		}
	}
	
	if (time.minute == 10)
	{
		// 司令部不止一个武士
		ReportHeadWarriors(red);
		red->CheckTaken();
		
		for (int i = 1; i < g_city_vector.size()-1; i++)
		{
			City* city = g_city_vector[i];
			Warrior* redWarrior = city->GetWarrior("red");
			Warrior* blueWarrior = city->GetWarrior("blue");
			
			if (redWarrior != NULL)
			{
				redWarrior->ReportPosition();
			}
			if (blueWarrior != NULL)
			{
				blueWarrior->ReportPosition();
			}
		}
		
		ReportHeadWarriors(blue);
		
		// 本地的战士派出去了，直接检查本地的战士数量
		blue->CheckTaken();
	}
	
	if (time.minute == 30)
	{
		
		for (int i = 1; i < g_city_vector.size()-1; i++)
		{
			City* city = g_city_vector[i];
			Warrior* redWarrior = city->GetWarrior("red");
			Warrior* blueWarrior = city->GetWarrior("blue");
			
			if (redWarrior != NULL)
			{
				redWarrior->CheckCityLife();
			}
			if (blueWarrior != NULL)
			{
				blueWarrior->CheckCityLife();
			}
		}
	}
	
	if (35 == minute)
	{
		// bomb
		for (int i = 1; i < g_city_vector.size()-1; i++)
		{
			City* city = g_city_vector[i];
			Warrior* redWarrior = city->GetWarrior("red");
			Warrior* blueWarrior = city->GetWarrior("blue");
			
			if (redWarrior != NULL)
			{
				redWarrior->CheckArrow();
			}
			if (blueWarrior != NULL)
			{
				blueWarrior->CheckArrow();
			}
		}
	}
	
	if (38 == minute)
	{
		// bomb
		for (int i = 1; i < g_city_vector.size()-1; i++)
		{
			City* city = g_city_vector[i];
			Warrior* redWarrior = city->GetWarrior("red");
			Warrior* blueWarrior = city->GetWarrior("blue");
			
			if (redWarrior != NULL)
			{
				redWarrior->CheckBomb();
			}
			if (blueWarrior != NULL)
			{
				blueWarrior->CheckBomb();
			}
		}
	}
	
	if (40 == minute)
	{
		g_blue_battle_life = 0;
		g_red_battle_life = 0;
		// Fight!!!
		for (int i = 1; i < g_city_vector.size()-1; i++)
		{
			City* city = g_city_vector[i];
			// if (i == )
				
			if (city->GetWarriorCount() == 2)
			{
				Warrior* redWarrior = city->GetWarrior("red");
				Warrior* blueWarrior = city->GetWarrior("blue");

				Fight(city, redWarrior, blueWarrior);
				
			} else {
				// 一个也有可能死亡
				Warrior* redWarrior = city->GetWarrior("red");
				Warrior* blueWarrior = city->GetWarrior("blue");
				if (redWarrior!=NULL && redWarrior->IsDead())
				{
					redWarrior->Die();
				}
				if (blueWarrior != NULL && blueWarrior->IsDead())
				{
					blueWarrior->Die();
				}
			}
			// 战士最后死亡
		}
		
		red->AwardAll();
		blue->AwardAll();
		
		red->life += g_red_battle_life;
		blue->life += g_blue_battle_life;
		
		// 之前在循环体里面导致异常
		g_red_battle_life = 0;
		g_blue_battle_life = 0;
		
		// cout << red->GetFullName() << ",get " << g_red_battle_life << endl;
		// cout << blue->GetFullName() << ",get " << g_blue_battle_life << endl;
	}
	
	if (time.minute == 55)
	{
	}
}

void Weapon::Weaken()
{
	atk = atk * 0.8;
}


// 全局变量
GameWorld g_world; // 全局世界

int main()
{
    int groupNum;

    cin >> groupNum;

    vector<InputGroup> inputVector;
	
	// test vector
	/*
	vector<int> vv;
	vv.push_back(1);
	vv.push_back(2);
	
	for(vector<int>::iterator it = vv.begin(); it != vv.end(); it++)
	{
		cout << *it << endl;
	}
	*/

    int n = 1;
    while (n <= groupNum) {
        // int totalLife;
        // int dragon_life, ninja_life, iceman_life, lion_life, wolf_life;

        InputGroup group;

        cin >> group.totalLife 
			>> group.cityCount
        	>> group.arrowDamage
        	>> group.loyaltyDec // lion每次忠诚度减少的值
			>> group.totalTime;
			 
        cin >> group.dragon_life 
			>> group.ninja_life 
			>> group.iceman_life 
			>> group.lion_life 
			>> group.wolf_life;
			
		cin >> group.dragon_atk
			>> group.ninja_atk
			>> group.iceman_atk
			>> group.lion_atk
			>> group.wolf_atk;

        inputVector.push_back(group);

        n +=1;
    }
    
    // char name[5] = "test";
	// char other[5];
	
	// *other = *name;
	// cout << other << endl; 

    int i = 0;
    for (i = 0; i < inputVector.size(); i++) {
        InputGroup group = inputVector[i];
        HeadQuarter red("red");
		HeadQuarter blue("blue");
		
		g_world.red = &red;
		g_world.blue = &blue;
		
		// 初始化城市
		g_total_city_count = group.cityCount;
		g_arrow_atk = group.arrowDamage;
		g_loyalty_decrement = group.loyaltyDec;
		g_max_id = 0;
		
		red.number = 0;
		blue.number = g_total_city_count + 1;
		
		g_world.InitCities(g_total_city_count, &red, &blue);

        Dragon dragon;
        Lion lion;
        Iceman iceman;
        Ninja ninja;
        Wolf wolf;
        
        dragon.SetLife(group.dragon_life);
        dragon.atk = group.dragon_atk; 
        
        ninja.SetLife(group.ninja_life);
        ninja.atk = group.ninja_atk;
        
        iceman.SetLife(group.iceman_life);
        iceman.atk = group.iceman_atk;
        
        lion.SetLife(group.lion_life);
		lion.atk = group.lion_atk;
        
        wolf.SetLife(group.wolf_life);
        wolf.atk = group.wolf_atk;

        red.life  = group.totalLife;
        blue.life = group.totalLife;

        red.AddWarriorPrototype(iceman.Clone());
        red.AddWarriorPrototype(lion.Clone());
        red.AddWarriorPrototype(wolf.Clone());
        red.AddWarriorPrototype(ninja.Clone());
        red.AddWarriorPrototype(dragon.Clone());

        blue.AddWarriorPrototype(lion.Clone());
        blue.AddWarriorPrototype(dragon.Clone());
        blue.AddWarriorPrototype(ninja.Clone());
        blue.AddWarriorPrototype(iceman.Clone());
        blue.AddWarriorPrototype(wolf.Clone());

        cout << "Case " << i+1 << ":" << endl;
        
        g_time.Clear();

        while (red.NotStop() && blue.NotStop()) {
        	
        	if (g_time.totalMinute > group.totalTime)
        	{
        		break;
			}
			red.Step(g_time);
			blue.Step(g_time);
			g_world.Step(g_time);
			
			// 最后更新时间
            g_time.Step();
        }
        cout << flush;
    }
    // 释放资源 
    g_world.ReleaseCities();
    return 0;
}
