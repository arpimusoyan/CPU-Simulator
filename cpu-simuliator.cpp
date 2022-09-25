#include <iostream>
#include <fstream>
#include <string>
#include <map>
std::map<std::string, int> mp;
struct keywords
{
   std::string mov = "imov";
   std::string add = "iadd";
   std::string sub = "isub";
   std::string mul = "imul";
   std::string div = "idiv";
   std::string iand = "iand";
   std::string ior = "ior";
}inst;
​
struct reg 
{
   std::string r1 = "r1";
   std::string r2 = "r2";
   std::string r3 = "r3";
}regi;
int string_int (std::string str)
{
​
   int sum=0, j = 0;
   bool fl =false;
   if(str[j]=='-'){
   j++;
   fl = true;
   }
    while(j!= str.size())
    {
      sum = sum*10 + (str[j]-'0');
      j++;
    }
 return !fl ? sum : (-1*sum);
​
}
int change_string (std::string str,int i)
{
   std::string m;
   bool fl =false;
   int sum=0, j = 0;
   if(str[i] == 'r')
      {
         while(i < str.size())
         {
            m += str[i];
            i++;
         }
         return mp[m];
      }
   if(str[i]=='-'){
   i++;
   fl = true;
   }
   while(i!=str.size())
   {
     m+=str[i];
     i++;
   }
   
    while(j!= m.size())
    {
      sum = sum*10 + (m[j]-'0');
      j++;
    }
 return !fl ? sum : (-1*sum);
}
void mull(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }
​
   if(r2[0]=='r')
    {
      mp[r1] *= mp[r2];
    }
    else
    {
      mp[r1] *= string_int (r2);
    }
    
}
void andd(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }
​
   if(r2[0]=='r')
    {
      mp[r1] &= mp[r2];
    }
    else
    {
      mp[r1] &= string_int (r2);
    }
    
}
void orr(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }
​
   if(r2[0]=='r')
    {
      mp[r1] |= mp[r2];
    }
    else
    {
      mp[r1] |= string_int (r2);
    }
    
}
void divv(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }
   if(r2[0]=='r')
    {
      if(mp[r2] == 0)
      std::cout << "Error " << std::endl;
      else
      mp[r1] /= mp[r2];
    }
    else
    {
       if(string_int(r2))
      mp[r1] /= string_int(r2);
      else
      std::cout << "Error " << std::endl;
    }
    
}
void subb (std::string str,int i)
{
​
std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }
​
   if(r2[0]=='r')
    {
mp[r1] -= mp[r2];
    }
    else
    {
      mp[r1] -= string_int(r2);
    }
    
}
void addi(std::string str, int i)
{
   std::string r1,r2;
  while(str[i] != ','){
    r1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    r2+=str[i];
    i++;
  }
​
   if(r2[0]=='r')
    {
      mp[r1] += mp[r2];
    }
    else
    {
      mp[r1] += string_int(r2);
    }
    
}
void cmp_reg (std::string str,int i)
{
   std::string m;
   while(str[i]!=',')
   {
     m+=str[i];
     i++;
   }
    if (m == regi.r1) {
        mp[m] = change_string(str, i+1);
         return;
      }
      if (m == regi.r2) {
        mp[m] = change_string(str, i+1);
         return;
      }
      if (m == regi.r3) {
         
          mp[m] = change_string(str, i+1);
         return;
         
      }
​
}
void dec(std::string str)
{
   std::string str1;
   for(int i = 0; i < str.size();i++)
   {
      while(str[i] != ' '){
        str1 += str[i];
        i++;
      }
      if (str1 == inst.mov) {
            cmp_reg(str, i+1);
         return;
      }
      if (str1 == inst.add) {
          addi(str, i+1);
         return;  
      }
      if (str1 == inst.sub) {
          subb(str, i+1);
         return;  
      }
      if (str1 == inst.mul) {
          mull(str, i+1);
         return;  
      }
      if (str1 == inst.div) {
          divv(str, i+1);
         return;  
      }
      if (str1 == inst.iand) {
          andd(str, i+1);
         return;  
      }
      if (str1 == inst.ior) {
          orr(str, i+1);
         return;  
      }
     
   }
}
​
int main()
{
  std::ifstream text("cpu.txt");
  std::string str;
 
  
  if(!text.is_open())
  {
    std::cout << "File open error " << std::endl;
  }
 else
 {
   while(!text.eof())
   {
      getline(text,str);
      dec(str);
   }
 }
  text.close();
 return 0;
}