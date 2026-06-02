class Solution {
 public:
  int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                         vector<int>& waterStartTime,
                         vector<int>& waterDuration) {
    int l = 0, w = 0;
    vector<pair<int, int>> land, water;
    int n = landStartTime.size();
    int m = waterStartTime.size();
    for (int i = 0; i < n; i++) {
      land.push_back({landStartTime[i], landDuration[i]});
    }
    for (int i = 0; i < m; i++) {
      water.push_back({waterStartTime[i], waterDuration[i]});
    }

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int time1 = 0, time2 = 0;
        time1 = max(land[i].first, time1);
        time1 += land[i].second;

        time1 = max(water[j].first, time1);
        time1 += water[j].second;

        time2 = max(water[j].first, time2);
        time2 += water[j].second;

        time2 = max(land[i].first, time2);
        time2 += land[i].second;
        ans = min(ans, min(time1, time2));
      }
    }

    return ans;
  }
};