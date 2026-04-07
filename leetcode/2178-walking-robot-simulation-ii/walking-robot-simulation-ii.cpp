class Robot {
    int width, height;
    int perimeter;
    int steps = 0;
    bool moved = false;

public:
    Robot(int width, int height) {
        this->width = width;
        this->height = height;
        perimeter = 2 * (width + height) - 4;
    }
    
    void step(int num) {
        if (perimeter == 0) return;
        steps = (steps + num) % perimeter;
        moved = true;
    }
    
    vector<int> getPos() {
        int s = steps;

        if (s < width) return {s, 0};
        s -= width;

        if (s < height - 1) return {width - 1, s + 1};
        s -= (height - 1);

        if (s < width - 1) return {width - 2 - s, height - 1};
        s -= (width - 1);

        return {0, height - 2 - s};
    }
    
    string getDir() {
        // FIX: differentiate initial vs completed cycle
        if (steps == 0) {
            return moved ? "South" : "East";
        }

        int s = steps;

        if (s < width) return "East";
        s -= width;

        if (s < height - 1) return "North";
        s -= (height - 1);

        if (s < width - 1) return "West";

        return "South";
    }
};
/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */