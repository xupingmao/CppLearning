#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

#define WC_DEBUG 0

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


void PrintTime(int time) {
	
	#if USE_PRINTF
		printf("%03d ", time);
	#else
	if (time < 10) {
        // printf("00");
        cout << "00";
    } else if (time < 100) {
        // printf("0");
        cout << "0";
    }
    cout << time << " ";
	#endif

    // printf("%d ", time);
}

class Warrior
{
public:

	// char[] 没有定义拷贝函数 
    string name; 
    char time[5];
    int number;
    int lifeUnit; // 生命值 
    int loyalty;  // 忠诚度 
    float morale; // 士气 
    int count;
    char* group;
    class HeadQuarter* head;

    Warrior () {
		count = 0;
    }

    Warrior(const char* name) {
        this->name = name;
        count = 0;
    }

    virtual ~Warrior() {
    	#if WC_DEBUG
		cout << "Warrior destructor called" << endl;
		#endif
    }
    
    void SetLife(int life)
    {
    	lifeUnit = life;
	}

    Warrior* CreateNew() {
    	count += 1;
        Warrior* newWarrior = this->Clone();
        return newWarrior;
    }

    Warrior& operator=(int n) {
        lifeUnit = n;
        return *this;
    }

    void SetNumber(int number) {
        this->number = number;
    }

    void Born(int time, int count) {
    	// PrintNewLine(); 
        PrintTime(time);
        
        #if USE_PRINTF
        
        printf("%s %s %d born with strength %d,%d %s in %s headquarter\n",
            group, name.c_str(), number, lifeUnit, count, name.c_str(), group);
        
        #else
        cout << group << " " << name << " " << number 
            << " born with strength " << lifeUnit << "," << count << " " 
            << name << " in " << group << " headquarter" << endl;
        #endif
        
        ExtraOutput();
    }
    
    virtual void ExtraOutput(); 
    
    virtual Warrior* Clone()
    {
    	Warrior *w = new Warrior;
    	*w = *this;
    	return w;
	}
};

void Warrior::ExtraOutput()
{
	
}

// 武器
class Weapon
{
	int number;
	string name;
	
	public:
		Weapon()
		{
		}
		
		Weapon(string name, int number)
		{
			this->name = name;
			this->number = number;
		}
		~Weapon()
		{
			
		} 
		
		string GetName()
		{
			return name;
		}
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
}; 

class Lion : public Warrior
{

public:
	
	Lion()
	{
		name = "lion";
	}
	
	virtual Lion* Clone()
	{
		Lion* lion = new Lion;
		*lion = *this;
		return lion; 
	} 
	
	void ExtraOutput();
};

class Iceman : public Warrior
{

public:
	
	Iceman()
	{
		name = "iceman";
	}
	
	virtual Iceman* Clone()
	{
		Iceman* temp = new Iceman;
		*temp = *this;
		return temp; 
	} 
	
	void ExtraOutput();
};

void Iceman::ExtraOutput()
{
	Weapon weapon = WeaponFactory::makeWeapon(number);
	cout << "It has a " << weapon.GetName() << endl;
}

class Ninja: public Warrior
{

public:
	
	Ninja()
	{
		name = "ninja";
	}
	
	virtual Ninja* Clone()
	{
		Ninja* temp = new Ninja;
		*temp = *this;
		return temp; 
	} 
	
	void ExtraOutput();
	
};

void Ninja::ExtraOutput()
{
	Weapon w1 = WeaponFactory::makeWeapon(number);
	Weapon w2 = WeaponFactory::makeWeapon(number+1);
	cout << "It has a " << w1.GetName() << " and a " << w2.GetName() << endl;
}

class Wolf: public Warrior
{

public:
	
	Wolf()
	{
		name = "wolf";
	}
	
	virtual Wolf* Clone()
	{
		Wolf* wolf = new Wolf;
		*wolf = *this;
		return wolf; 
	} 
	
	void ExtraOutput();
	
};

void Wolf::ExtraOutput()
{
	
}
 
 
class HeadQuarter
{
public:

    char name[20];
    int totalLifeUnit;
    int remainLifeUnit;
    int minWarriorLife;
    vector<Warrior*> warriorPrototype;
    vector<int> warriorCountVector;
    int warriorIndex;
    int warriorNumber;
    char time[5];
    bool stoped;

    HeadQuarter(const char* name) {
        strcpy(this->name, name);
        this->warriorIndex = 0;
        this->minWarriorLife = -1;
        this->warriorIndex = 0;
        this->warriorNumber = 0;
        this->stoped = false;
    }
    ~HeadQuarter() {
		for(vector<Warrior*>::iterator it = warriorPrototype.begin(); it != warriorPrototype.end(); it++)
		{
			delete *it;
		}
    }
    
    HeadQuarter& operator=(int totalLifeUnit) {
        this->totalLifeUnit = totalLifeUnit;
        this->remainLifeUnit = totalLifeUnit;
        return *this;
    }

    void MakeWarrior(int time);
    Warrior* GetNextWarrior();
    void AddWarriorPrototype(Warrior *w);
    bool NotStop();
    int GetRemain();
	void AddWarrior(Warrior* w);
};

int HeadQuarter::GetRemain()
{
	return remainLifeUnit;
}

Warrior* HeadQuarter::GetNextWarrior() {
    int i = 0;
    for (i = 0; i < warriorPrototype.size(); i++) {
        warriorIndex = warriorIndex % warriorPrototype.size();
        Warrior *w = warriorPrototype[warriorIndex];
        warriorIndex += 1;
        if (w->lifeUnit <= remainLifeUnit) {
        	// w.count += 1;
            return w->CreateNew();
        }
    }
    return NULL;
}

void HeadQuarter::MakeWarrior(int time) {
    Warrior* w = GetNextWarrior();
    if (w == NULL) {
        if (!stoped) {
            PrintTime(time);
            #if USE_PRINTF
            printf("%s headquarter stops making warriors\n", name);
            #else
            cout << name << " headquarter stops making warriors" << endl;
            #endif
            // printf("%s headquarter stops making warriors\n", name);
            // PrintNewLine();
            stoped = true;
        }
        return;
    }
    remainLifeUnit -= w->lifeUnit;
    warriorNumber += 1;
    w->SetNumber(warriorNumber);
    w->Born(time, w->count);
    delete w;
}

bool HeadQuarter::NotStop() {
    // if (stoped) {
    //     return false;
    // }
    // return remainLifeUnit >= minWarriorLife;
    return !stoped;
}

void HeadQuarter::AddWarriorPrototype(Warrior* w) {
    if (minWarriorLife < 0) {
        minWarriorLife = w->lifeUnit;
    } else if (w->lifeUnit < minWarriorLife) {
        minWarriorLife = w->lifeUnit;
    }
    w->group = this->name;
    w->head = this;
    warriorPrototype.push_back(w);
}

void Dragon::ExtraOutput() {
	Weapon weapon = WeaponFactory::makeWeapon(number);
	morale = (float) head->GetRemain() / (float) this->lifeUnit;
	char buf[20];
	sprintf(buf, "%.2f", morale);
	cout << "It has a " << weapon.GetName() << ",and it's morale is " << buf << endl;
}

void Lion::ExtraOutput()
{
	cout << "It's loyalty is " << head->GetRemain() << endl;
}


class InputGroup {
public:
    int totalLifeUnit;
    int dragon_life;
    int ninja_life;
    int iceman_life;
    int lion_life;
    int wolf_life;
};

int main()
{
    int groupNum;

    cin >> groupNum;

    vector<InputGroup> inputVector;

    int n = 1;
    while (n <= groupNum) {
        // int totalLifeUnit;
        // int dragon_life, ninja_life, iceman_life, lion_life, wolf_life;

        InputGroup group;

        cin >> group.totalLifeUnit;
        cin >> group.dragon_life >> group.ninja_life >> group.iceman_life >> group.lion_life >> group.wolf_life;

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
        HeadQuarter red("red"), blue("blue");

        Dragon dragon;
        Lion lion;
        Iceman iceman;
        Ninja ninja;
        Wolf wolf;
        
        dragon.SetLife(group.dragon_life);
        lion.SetLife(group.lion_life);
        iceman.SetLife(group.iceman_life);
        ninja.SetLife(group.ninja_life);
        wolf.SetLife(group.wolf_life);

        red  = group.totalLifeUnit;
        blue = group.totalLifeUnit;

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

		#if USE_PRINTF
		printf("Case:%d\n", i+1);
		#else
        cout << "Case:" << i+1 << endl;
        #endif
        
        int time = 0;

        while (red.NotStop() || blue.NotStop()) {
            red.MakeWarrior(time);
            blue.MakeWarrior(time);
            time += 1;
        }
        #if USE_PRINTF
        fflush(stdout);
        #else
        cout << flush; 
        #endif
    }
    return 0;
}
