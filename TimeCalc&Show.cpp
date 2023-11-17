#include <iostream>
#include<iomanip>
using namespace std;

enum struct DaylightSaving
{
   summerTime, winterTime, unknown
};
class Clock
{
private:
    unsigned int hour, minute;
    DaylightSaving daylightSaving;
public:
    class HourTooBig : public exception { };
    class MinuteTooBig : public exception { };
    Clock() : hour(0), minute(0), daylightSaving(DaylightSaving::unknown)
    {

    }
    Clock(unsigned int h, unsigned int m, DaylightSaving dls) :  hour(h), minute(m), daylightSaving(dls)
    {
        if (h > 23)
        {
            throw HourTooBig();
        }
        if (m > 59)
        {
            throw MinuteTooBig();
        }

    }
    void set_daylightSaving (DaylightSaving d)
    { daylightSaving = d;}
    DaylightSaving get_daylightSaving()
    {
        return daylightSaving;
    }
    Clock& operator++()
    {
        Clock clk;
        clk.hour = ++hour;
        clk.minute = ++minute;
        if (minute > 59)
        {
            hour = hour +1;
            minute = 0;
        }
        if (hour > 23)
        {
            hour = 0;
        }
        return *this;
    }
      Clock& operator++(int)
    {
       if(hour > 23){
            hour = 0;
        }
        else if(minute > 59){
            minute = 0;
            hour += 1;    
        }
        else{
            hour += 1;
            minute += 1;
        } 
        return *this;
    }
    friend bool operator==(const Clock& c1,const Clock& c2)
    {
        if ((c1.hour == c2.hour) && (c1.minute == c2.minute))

            return true;
        else
            return false;

    }
    friend ostream& operator<<(ostream&, Clock&);

};
ostream& operator<<(ostream& out, Clock& c)
{ char x = ':';
out  << fixed << setw(2) << setfill('0') << c.hour << x;
out  << fixed << setw(2) << setfill('0') << c.minute << endl;
return out;
}
int main(void){
    Clock* clock1 = new Clock(0,5,DaylightSaving::winterTime);
    Clock clock2(23,9,DaylightSaving::summerTime);
    Clock* clock3;
    clock1->set_daylightSaving(DaylightSaving::summerTime);
    for(int i =0; i<120; i++){
        clock2++;
    }
    unsigned int inputedHour, inputedMinute;
    try {
        cout<<"hour: ";
        cin>>inputedHour;
        cout<<"minute: ";
        cin>>inputedMinute;
        clock3 = new Clock(inputedHour, inputedMinute, DaylightSaving::unknown);
        if(clock2 == *clock3){
            cout<<"same time"<<endl;
        }
    }
    catch (Clock::HourTooBig){
        clock3 = new Clock();
    }
    catch (Clock::MinuteTooBig){
        clock3 = new Clock();
    }
    clock3 = new Clock;
    cout<<*clock1<<clock2<<*clock3;
    delete clock1;
    delete clock3;
    return 0;
}