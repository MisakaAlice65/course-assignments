#include <iostream>  
#include <cstring>  
  
class Chicken  
{  
    private:  
        int age = 24;  
        char *name = nullptr;  
  
    public:  
        Chicken() {}; 
  
        Chicken(int _age) : age(_age) {};  //Chicken c1(35);
  
        Chicken(int _age, const char *_name) : age(_age)  
        {  
            setName(_name);  
        };  
  

        
        //复制构造函数用于创建新对象
        
    	//赋值运算符用于更新已经存在的对象
        
        
        // 复制构造函数 ：创造出现有对象的副本 
        Chicken(const Chicken& other) : age(other.age)   
        {                                               
            setName(other.name);  
        };  
  
        ~Chicken()  //对象被清除时自动调用，防止内存泄露 
        {  
            if (name != nullptr)  
                delete[] name;  
        }  
  
        // 赋值运算符：更新对象 
        Chicken& operator=(const Chicken& other)      //Chicken c3 = c1; 或者//Chicken c3;   c3=c1; 
        {  
            if (this != &other)  
            {  
                setAge(other.age);  
                setName(other.name);  
            }  
            return *this;  
        }  
  
        void setAge(int _age)  
        {  
            age = _age;  
        }  
  
        void setName(const char *_name)  
        {  
            if(name != nullptr)  
                delete[] name;  
            int len = strlen(_name) + 1;  
            name = new char[len];  
            strcpy(name, _name);  
        }  
  
        const char *getName() const  
        {  
            return name;  
        }  
  
        int getAge() const  
        {  
            return age;  
        }  
};  
