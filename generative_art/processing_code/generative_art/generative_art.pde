import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

// FOR VERTICAL ORIENTATION
//int screenHeight = 768;
//int screenWidth = 8000;

// Scaled down 5 times for local work
//int screenHeight = 154;
//int screenWidth = 1600;

// FOR HORIZONTAL ORIENTATION
//int screenWidth = 4608;
//int screenHeight = 1360;

// Scaled down 4 times for local work 
int screenWidth = 1152;
int screenHeight = 340;

// The number of screens the installation will be displayed across
int numRects = 6;
int xMultiplier = screenWidth / numRects;

/**
The number of factors/populations we will base generative art on.
We are using male/female for this, so it's 2.
**/
int numFactors = 2;
int yMultiplier = screenHeight / (numFactors + 1);

int circleRadius = screenHeight / 7;
int circleCount = 0;

int femaleColor = color(180, 43, 106);
int maleColor = color(136, 196, 230);

color [] circleColors = {femaleColor, maleColor};
String [] ids = {"female", "male"};

// ConcurrentHashMap of all the generated circles
ConcurrentHashMap<Integer, GCircle> gCircles;

// JSONArray to store boundary coords of the screens
JSONArray boundaryCoords;

// String dicts of stats of progression between phases
IntDict toHighSchool;
IntDict toCollege;
IntDict toEntryLevel;
IntDict toSeniorLevel;
IntDict toExecLevel;


void settings() {  
  size(screenWidth, screenHeight);
}

void setup() {
    boundaryCoords = new JSONArray();
    gCircles = new ConcurrentHashMap<Integer, GCircle>();
    
    for (int i = 0; i < numRects; i++) {
      int boundaryX = xMultiplier * i;
      
      JSONObject currBoundCoords = new JSONObject();
      
      currBoundCoords.setInt("left_bound", boundaryX);
      currBoundCoords.setInt("right_bound", boundaryX + xMultiplier);
      currBoundCoords.setInt("upper_bound", 0);
      currBoundCoords.setInt("lower_bound", screenHeight);
      
      boundaryCoords.setJSONObject(i, currBoundCoords);
    }
    
    // Setup stats dict for progression to high school 
    //TODO: add sources
    // 80% of AP CS exam takers were male, 20% female in 2020
    toHighSchool = new IntDict();
    toHighSchool.set("male", 80);
    toHighSchool.set("female", 20);
    
    // 82% of CS majors in US are male, 18% female
    toCollege = new IntDict();
    toCollege.set("male", 82);
    toCollege.set("female", 18);
    
    // 81% of entry level SWEs are male, 19% female
    toEntryLevel = new IntDict();
    toEntryLevel.set("male", 19);
    toEntryLevel.set("female", 19);
    
    // 84% of mid to senior level SWEs are male, 16% female
    toSeniorLevel = new IntDict();
    toSeniorLevel.set("male", 84);
    toSeniorLevel.set("female", 16);
    
    // 90% of executives in tech are male, 10% female
    toExecLevel = new IntDict();
    toExecLevel.set("male", 90);
    toExecLevel.set("female", 10);


    addCircle("male");
    addCircle("female");
}


void draw() {
    background(0, 0, 0);
    
    for (int i = 0; i < numRects; i++) {
      stroke(255, 255, 255);
      int currBoundaryX = boundaryCoords.getJSONObject(i).getInt("left_bound");
      line(currBoundaryX, 0, currBoundaryX, screenHeight);
    }

    for(Map.Entry<Integer, GCircle> entry : gCircles.entrySet()) {
      GCircle gCircle = entry.getValue();
      if (gCircle.currPanel >= numRects) {
        gCircles.remove(gCircle.index);
      } else {
        gCircle.move();
        gCircle.display();
      }
    }
    
        
}

// Function to create circles in first stage
void addCircle(String identity) {
    color fc = color(0, 0, 0);
    
    // TODO: hacky, try to fix
    int yInd = 0;
    switch(identity) {
      case "male":
        fc = circleColors[1];
        yInd = 1;
        break;
      case "female":
        fc = circleColors[0];
        yInd = 0;
        break;
    }
  
  int circleX = boundaryCoords.getJSONObject(0).getInt("left_bound") + (xMultiplier / 2);
  int circleY = boundaryCoords.getJSONObject(0).getInt("upper_bound") + (yMultiplier * (yInd + 1));
  
  PVector loc = new PVector(circleX, circleY);
  PVector vel = new PVector(1, 0);
  PVector g = new PVector(0.2, 0);
  
  
  int currPanel = 0;
  
  GCircle currCircle = new GCircle(circleCount, circleX, circleY, circleRadius, currPanel, fc, identity, loc, vel, g);
  gCircles.put(circleCount, currCircle);
  circleCount++;
  
}

// Class for the generated circles
class GCircle {
  int index;       // index of the circle in the GCircles array
  float initialX;  // initial x position of the center of the circle
  float initialY;  // initial y position of the center of the circle
  float circleR;   // radius of the circle
  int currPanel;   // the index of the screen the circle is currently in
  color fillColor; // the color the circle will appear
  String id;       // an id for the circle
  
  // Most vector logic comes from "Bouncing Ball with Vectors" by Daniel Shiffman in Processing docs
  PVector location;  // location of the circle 
  PVector velocity;  // velocity of the circle
  PVector gravity;   // gravity/acceleration of the circle
  
  int bounceCount;   // The number of times a ball has bounced on the wall
  
  GCircle(int i, float ix, float iy, float cr, int cp, color fc, String identity, PVector loc, PVector vel, PVector g) {
    index = i;
    initialX = ix;
    initialY = iy;
    circleR = cr;
    currPanel = cp;
    fillColor = fc;
    id = identity;
    location = loc;
    velocity = vel;
    gravity = g;
    bounceCount = 0;
  }
  
  void display() {
    fill(fillColor);
    noStroke();
    circle(location.x, location.y, circleR);
  }
  
  void move() {
    int currLeftBound =  boundaryCoords.getJSONObject(currPanel).getInt("left_bound");
    int currRightBound = boundaryCoords.getJSONObject(currPanel).getInt("right_bound");
    // Add velocity to the location.
    location.add(velocity);
    
    // Add gravity to the velocity
    velocity.add(gravity);

    if ((location.x > (currRightBound - circleR / 2)) || (location.x < (currLeftBound - (circleR / 2)))) {
      if (bounceCount == 0){
        println(velocity.x);
        // TODO: this is hacky, can i fix?
        velocity.x = 5.599999;
      }
      velocity.x = velocity.x * -0.97;
      bounceCount++;
      // Wait until it has bounced 10 times, otherwise moves too fast
      if (bounceCount > 10) {
        int chance = int(random(0, 100));
        int panelStat = getPanelStats(currPanel, id);
        if (chance <= panelStat) {
          progressToNextPanel();
        }
      }
    }
  }
  
  void progressToNextPanel() {
    currPanel++;
    if (currPanel < numRects) {
      location.x = boundaryCoords.getJSONObject(currPanel).getInt("left_bound");
      velocity.x = 1;
      gravity.x = 0.2;
      bounceCount = 0;
      addCircle(id);
    }
  }
  
  // Depending on the panel index, get the stats that balls have to reach in order to pass
  int getPanelStats(int cp, String identity) {
    int panelStat = 0;
    
    switch(cp) {
      case 0:
        panelStat = toHighSchool.get(identity);
        break;
      case 1:
        panelStat = toHighSchool.get(identity);
        break;
      case 2:
        panelStat = toHighSchool.get(identity);
        break;
      case 3:
        panelStat = toHighSchool.get(identity);
        break;
      case 4:
        panelStat = toHighSchool.get(identity);
        break;
      case 5:
        panelStat = toHighSchool.get(identity);
        break;
    }
    
    return panelStat;
  }
  
  
  
}
  
