#include <iostream>
using namespace std;
class Cube{
    private:
    int m_len;
    int m_wid;
    int m_het;
    public:
    int getCubeT(){
        return m_len*m_wid*m_het;
    }
    int getCubeS(){
        return 2*(m_len*m_wid+m_len*m_het+m_wid*m_het);
    }
    void setLen(int len){
        m_len=len;
    }
    void setWid(int wid){
        m_wid=wid;
    }
    void setHet(int het){
        m_het=het;
    }
    int getLen(){
        return m_len;
    }
    int getWid(){
        return m_wid;
    }
    int getHet(){
        return m_het;
    }
    bool isSameByClass(Cube &c){
        if(m_len==c.m_len&&m_wid==c.m_wid&&m_het==c.m_het){
            return true;
        }
        else{
            return false;
        }
    }
};
bool isSame(Cube &c1,Cube &c2){
    if(c1.getLen()==c2.getLen()&&c1.getWid()==c2.getWid()&&c1.getHet()==c2.getHet()){
        return true;
    }
    else{
        return false;
    }
}
int main(){
    Cube c1;
    Cube c2;
    c1.setLen(10);
    c1.setWid(10);
    c1.setHet(10);
    c2.setLen(10);
    c2.setWid(10);
    c2.setHet(10);
    cout<<"c1的体积是:"<<c1.getCubeT()<<endl;
    cout<<"c2的体积是:"<<c2.getCubeT()<<endl;
    if(isSame(c1,c2)){
        cout<<"c1和c2是相同的立方体"<<endl;
    }
    else{
        cout<<"c1和c2不是相同的立方体"<<endl;
    }
    if(c1.isSameByClass(c2)){
        cout<<"c1和c2是相同的立方体"<<endl;
    }
    else{
        cout<<"c1和c2不是相同的立方体"<<endl;
    }
    system("pause");
    return 0;
}