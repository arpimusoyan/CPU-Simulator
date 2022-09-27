#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<std::string, int> umap;

struct keywords
{
   std::string mov = "umov";
   std::string add = "uadd";
   std::string sub = "usub";
   std::string mul = "umul";
   std::string div = "udiv";
   std::string uand = "uand";
   std::string uor = "uor";
}instruct;

struct registers 
{
   std::string r1 = "r1";
   std::string r2 = "r2";
   std::string r3 = "r3";
}reg;

int string_to_int (std::string str)
{
   int sum = 0, j = 0;
   bool fls = false;
   if(str[j]=='-'){
   j++;
   fls = true;
   }
    while(j!= str.size())
    {
      sum = sum*10 + (str[j]-'0');
      j++;
    }
 return !fls ? sum : (-1*sum);
 
 }
int transform_string (std::string str,int i)
{
   std::string s;
   bool fls =false;
   int sum = 0, j = 0;
   if(str[i] == 'r')
      {
         while(i < str.size())
         {
            s += str[i];
            i++;
         }
         return umap[s];
      }
   if(str[i]=='-'){
   i++;
   fls = true;
   }
   while(i!=str.size())
   {
     s +=str[i];
     i++;
   }
   
    while(j!= s.size())
    {
      sum = sum*10 + (s[j]-'0');
      j++;
    }
 return !fls ? sum : (-1*sum);
}
void umul (std::string str, int i)
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
      umap[r1] *= umap[r2];
    }
    else
    {
      umap[r1] *= string_to_int (r2);
    }
    
}
void uand(std::string str, int i)
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
      umap[r1] &= umap[r2];
    }
    else
    {
      umap[r1] &= string_to_int (r2);
    }
    
}
void uor(std::string str, int i)
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
      umap[r1] |= umap[r2];
    }
    else
    {
      umap[r1] |= string_to_int (r2);
    }
    
}
void udiv(std::string str, int i)
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
      if(umap[r2] == 0)
      std::cout << "Error " << std::endl;
      else
      umap[r1] /= umap[r2];
    }
    else
    {
       if(string_to_int(r2))
      umap[r1] /= string_to_int(r2);
      else
      std::cout << "Error " << std::endl;
    }
}
    
void usub (std::string str,int i)
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
umap[r1] -= umap[r2];
    }
    else
    {
      umap[r1] -= string_to_int(r2);
    }
    
}
void uadd (std::string str, int i)
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
      umap[r1] += umap[r2];
    }
    else
    {
      umap[r1] += string_to_int(r2);
    }
    
}
void ucmp (std::string str,int i)
{
   std::string m;
   while(str[i]!=',')
   {
     m+=str[i];
     i++;
   }
    if (m == reg.r1) {
        umap[m] = transform_string(str, i+1);
         return;
      }
      if (m == reg.r2) {
        umap[m] = transform_string(str, i+1);
         return;
      }
      if (m == reg.r3) {
         
          umap[m] = transform_string(str, i+1);
         return;
         
      }
}
void udec(std::string str)
{
   std::string str1;
   for(int i = 0; i < str.size();i++)
   {
      while(str[i] != ' '){
        str1 += str[i];
        i++;
      }
      if (str1 == instruct.mov) {
            ucmp (str, i+1);
         return;
      }
      if (str1 == instruct.add) {
          uadd(str, i+1);
         return;  
      }
      if (str1 == instruct.sub) {
          usub(str, i+1);
         return;  
      }
      if (str1 == instruct.mul) {
          umul(str, i+1);
         return;  
      }
      if (str1 == instruct.div) {
          udiv(str, i+1);
         return;  
      }
      if (str1 == instruct.uand) {
          uand(str, i+1);
         return;  
      }
      if (str1 == instruct.uor) {
          uor(str, i+1);
         return;  
      }
     
   }
}
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
      udec(str);
   }
 }
  text.close();
 return 0;
}
