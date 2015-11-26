#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
class BigInt
{
private:
    int m_iUp, m_iDown;
public:
    BigInt():m_iUp(0), m_iDown(0) {}
    BigInt(int down):m_iUp(0), m_iDown(down) {}
    BigInt(int up, int down):m_iUp(up), m_iDown(down) {}
    BigInt &operator+(const BigInt &rhs)
    {
        int iMax = 100000000;
        m_iUp += rhs.m_iUp;
        m_iDown += rhs.m_iDown;
        if (m_iDown >= iMax)
        {
            m_iUp += m_iDown / iMax;
            m_iDown %= iMax;
            if (m_iUp < 0)
                fprintf(stderr, "m_iUp less than zero!!\n");
        }
        return *this;
    }
    int up() const
    {
        return m_iUp;
    }
    int down() const
    {
        return m_iDown;
    }
};
std::map<int, BigInt> bankMap;
BigInt f(int n)
{
    if (n < 0) return BigInt();
    if (n <= 1) return BigInt(1);
    std::map<int, BigInt>::iterator iter = bankMap.find(n);
    if (iter == bankMap.end())
    {
        bankMap[n] = f(n - 1) + f(n - 2);
    }
    return bankMap[n];
}
int main(int argc, char *argv[])
{
    if (argc < 2) printf("please input n and retry\n");
    else
    {
        BigInt ans = f(atoi(argv[1]));
        char buf[64];
        std::string strAns;
        if (ans.up() > 0)
        {
            sprintf(buf, "%d", ans.up());
            strAns = buf;
        }
        sprintf(buf, "%d", ans.down());
        strAns += buf;
        printf("Answer is [%s]\n", strAns.c_str());
    }
    return 0;
}

