#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;


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

    char name[20];
    char time[5];
    int number;
    int lifeUnit;
    int count;
    char* group;

    Warrior () {
		count = 0;
    }

    Warrior(const char* name) {
        strcpy(this->name, name);
        count = 0;
    }

    ~Warrior() {

    }

    Warrior* CreateNew() {
    	count += 1;
        Warrior* newWarrior = new Warrior;
        *newWarrior = *this;
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
            group, name, number, lifeUnit, count, name, group);
        
        #else
        cout << group << " " << name << " " << number 
            << " born with strength " << lifeUnit << "," << count << " " 
            << name << " in " << group << " headquarter" << endl;
        #endif
    }
};

class HeadQuarter
{
public:

    char name[20];
    int totalLifeUnit;
    int remainLifeUnit;
    int minWarriorLife;
    vector<Warrior> warriorPrototype;
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

    }
    
    HeadQuarter& operator=(int totalLifeUnit) {
        this->totalLifeUnit = totalLifeUnit;
        this->remainLifeUnit = totalLifeUnit;
        return *this;
    }

    void MakeWarrior(int time);
    Warrior* GetNextWarrior();
    void AddWarriorPrototype(Warrior w);
    bool NotStop();
};

Warrior* HeadQuarter::GetNextWarrior() {
    int i = 0;
    for (i = 0; i < warriorPrototype.size(); i++) {
        warriorIndex = warriorIndex % warriorPrototype.size();
        Warrior &w = warriorPrototype[warriorIndex];
        warriorIndex += 1;
        if (w.lifeUnit <= remainLifeUnit) {
        	// w.count += 1;
            return w.CreateNew();
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

void HeadQuarter::AddWarriorPrototype(Warrior w) {
    if (minWarriorLife < 0) {
        minWarriorLife = w.lifeUnit;
    } else if (w.lifeUnit < minWarriorLife) {
        minWarriorLife = w.lifeUnit;
    }
    w.group = this->name;
    warriorPrototype.push_back(w);
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

    int i = 0;
    for (i = 0; i < inputVector.size(); i++) {
        InputGroup group = inputVector[i];
        HeadQuarter red("red"), blue("blue");

        Warrior dragon("dragon"), 
            ninja("ninja"), 
            iceman("iceman"), 
            lion("lion"), 
            wolf("wolf");


        dragon = group.dragon_life;
        ninja  = group.ninja_life;
        iceman = group.iceman_life;
        lion   = group.lion_life;
        wolf   = group.wolf_life;

        red  = group.totalLifeUnit;
        blue = group.totalLifeUnit;

        red.AddWarriorPrototype(iceman);
        red.AddWarriorPrototype(lion);
        red.AddWarriorPrototype(wolf);
        red.AddWarriorPrototype(ninja);
        red.AddWarriorPrototype(dragon);

        blue.AddWarriorPrototype(lion);
        blue.AddWarriorPrototype(dragon);
        blue.AddWarriorPrototype(ninja);
        blue.AddWarriorPrototype(iceman);
        blue.AddWarriorPrototype(wolf);

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
