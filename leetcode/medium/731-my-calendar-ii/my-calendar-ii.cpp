class MyCalendarTwo {
  map<int, int> event;

 public:
  MyCalendarTwo() {}

  bool book(int startTime, int endTime) {
    event[startTime] += 1;
    event[endTime] -= 1;
    int b = 0;
    int maxb = 0;
    for (auto &e : event) {
      b += e.second;
      if (b > maxb) {
        maxb = b;
      }
    }
    if (maxb > 2) {
      event[startTime] -= 1;
      event[endTime] += 1;
      return false;
    }
    return true;
  }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(startTime,endTime);
 */