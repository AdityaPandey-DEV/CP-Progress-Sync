class MyCalendarThree {
    map<int,int>event;
public:
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        event[startTime]+=1;
        event[endTime]-=1;
        int b=0;
        int maxb=0;
        for(auto &e:event){
            b+=e.second;
            if(b>maxb){
                maxb=b;
            }
        }
        return maxb;
        

    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */