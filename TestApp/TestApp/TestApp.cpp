#include <iostream>
#include <vector>
using namespace std;

class Phone
{
public:
    void Call()
        { 
            cout << "Phone CAll" << endl; 
        }
};

class Laptop 
{
public:
    void Code() 
    { 
        cout << "Latpop Code" << endl; 
    }
};
class Device 
{
    Laptop laptop;  
    Phone phone;  
public:
    void PowerOn() 
    {
        laptop.Code();
        phone.Call();
        std::cout << "Device PowerOn" << std::endl;
    }
};


class Engine
{
public:
    void Ignite()
    {
        cout << "Engine ignite" << endl;
    }
};
class Sheild
{
public:
    void Activate()
    {
        cout << "Sheild Activate" << endl;
    }
};
class Spaceship
{
private:
    Engine engine;
    Sheild shield;

public:
    void Launch()
    {
        engine.Ignite();
        shield.Activate();
        cout << "Spaceship Luanch" << endl;
    }
};

class Renderer {
public:
    virtual void Draw()
    {
        cout << "Draw" << endl;
    }
    virtual ~Renderer() = default;
};

class Sprite : public Renderer{
public:
    void Draw() /*const override*/
    {
        cout << "Draw Sprite" << endl;
    }
};

class Text : public Renderer{
    void Draw() /*const override*/
    {
        cout << "Draw Text" << endl;
    }
};

int main() {

    // 1)
    Device device;
    device.PowerOn();

    // 2)
    Spaceship spaceship;
    spaceship.Launch();

    // 3)
    vector<Renderer*> renderer;
    renderer.push_back(new Sprite());
    renderer.push_back(new Text());

    for (auto render : renderer) 
        render->Draw(); 

    for (auto render : renderer) 
        delete render; 

    return 0;
}




//#include <iostream>
//using namespace std;
//
//bool is_leap(int y)
//{
//	bool answer = false;
//
//	if (y % 400 == 0)
//		answer = true;
//
//	else if (y % 4 == 0)
//	{
//		answer = true;
//
//		if (y % 100 == 0)
//			answer = false;
//	}
//
//
//	return answer;
//}
//
//int main()
//{
//	cout << boolalpha << is_leap(2000) << " " << is_leap(1900) << " " << is_leap(2024) << "\n"; // true false true
//}