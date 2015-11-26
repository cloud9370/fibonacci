#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
class BigInt
{
private:
    std::string m_strValue;
public:
    BigInt():m_strValue("0") {}
    BigInt(int n):m_strValue()
    {
        char buf[64]; sprintf(buf, "%d", n);
        m_strValue = buf;
    }
    BigInt operator+(const BigInt &rhs)
    {
        std::vector<int> resVec;
        size_t nMin, nMax; nMin = nMax = rhs.m_strValue.length();
        if(nMin > m_strValue.length()) nMin = m_strValue.length();
        if(nMax < m_strValue.length()) nMax = m_strValue.length();
        int iInc = 0;
        for(int i=0;i<(int)nMax;i++)
        {
            char cL=0, cR=0;
            if(i<(int)m_strValue.length())
            {
                int iL = m_strValue.length() - i - 1;
                cL = m_strValue[(size_t)iL] - '0';
            }
            if(i<(int)rhs.m_strValue.length())
            {
                int iR = rhs.m_strValue.length() - i - 1;
                cR = rhs.m_strValue[(size_t)iR] - '0';
            }
            int iSum = cL + cR + iInc;
            if(iSum > 0)
            {
                iInc = iSum / 10;
                iSum %= 10;
            }
            else iInc = 0;
            resVec.push_back(iSum);
        }
        if(iInc>0) resVec.push_back(iInc);
        std::string strRet = "";
        for(int i=resVec.size()-1;i>=0;i--)
        {
            strRet += (char)resVec[i] + '0';
        }
        BigInt bigInt; bigInt.m_strValue = strRet;
        return bigInt;
    }
    std::string &getValue() { return m_strValue; }
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
        printf("Answer is [%s]\n", ans.getValue().c_str());
    }
    return 0;
}

