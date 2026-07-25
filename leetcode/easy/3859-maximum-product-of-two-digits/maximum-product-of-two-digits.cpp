class Solution {
public:
    int maxProduct(int n) {
        priority_queue<int>pq;
        while(n){
            int r=n%10;
            n=n/10;
            pq.push(r);
        }
        int a=pq.top();
        pq.pop();
        int b=pq.top();
        return a*b;
    }
};