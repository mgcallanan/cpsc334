import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

// Scaled down 4 times for local work 
int screenWidth = 1152;
int screenHeight = 340;

float initialGravity = -0.2;
float initialVelocity = -1;

// For screen configurations
JSONArray screenCoords;

/**
The number of factors/populations we will base generative art on.
We are using male/female for this, so it's 2.
**/
int numFactors = 2;
int yMultiplier = screenHeight / (numFactors + 1);

int circleRadius = screenHeight / 7;
int circleCount = 0;

int femaleColor = color(180, 43, 106, 200);
int maleColor = color(136, 196, 230, 200);

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


// Variables for panel background color changes
// blue to pink color gradient array
color black = color(0, 0, 0);
color blue1 = color(0, 32, 235);
color blue2 = color(12, 30, 223);
color blue3 = color(28, 27, 208);
color blue4 = color(53, 24, 184);
color trueMid = color(82, 24, 157);
color pink4 = color(113, 25, 127);
color pink3 = color(124, 26, 113);
color pink2 = color(157, 32, 82);
color pink1 = color(229, 49, 36);

color [] pinkBlueColorGradient = {blue1, blue2, blue3, blue4, trueMid, pink4, pink3, pink2, pink1};

ArrayList<Panel> panels = new ArrayList<Panel>();


void setup() {
    fullScreen(0);
    screenCoords = new JSONArray();
  
    boundaryCoords = new JSONArray();
    
    parseScreenCoords();
        
    gCircles = new ConcurrentHashMap<Integer, GCircle>();
    
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
    
    for (int i = 0; i < boundaryCoords.size(); i++) {
      int currLeftBoundary = boundaryCoords.getJSONObject(i).getInt("left_bound");
      int currRightBoundary = boundaryCoords.getJSONObject(i).getInt("right_bound");
      int currLowerBoundary = boundaryCoords.getJSONObject(i).getInt("lower_bound");
      int currUpperBoundary = boundaryCoords.getJSONObject(i).getInt("upper_bound");
      stroke(255, 255, 255);
      fill(panels.get(i).backgroundColor);
      rect(currUpperBoundary, currLeftBoundary, currLowerBoundary - currUpperBoundary, currRightBoundary - currLeftBoundary);
    }

    for(Map.Entry<Integer, GCircle> entry : gCircles.entrySet()) {
      GCircle gCircle = entry.getValue();
      if (gCircle.currPanel >= boundaryCoords.size()) {
        gCircles.remove(gCircle.index);
      } else {
        gCircle.move();
        gCircle.display();
      }
    }   
}

void parseScreenCoords() {
  screenCoords = loadJSONArray("screen_coords.json");


  for (int i = 0; i < screenCoords.size(); i++) {
    JSONObject coord = screenCoords.getJSONObject(i);
    
    // Parsing JSON file for screen coords
    int topLeftX = coord.getInt("top_left_x");
    int topLeftY = coord.getInt("top_left_y");
    int bottomRightX = coord.getInt("bottom_right_x");
    int bottomRightY = coord.getInt("bottom_right_y");
    
    // Loading screen coords into generative art configuration
    
    // Have to swap x and y coordinates because of the Leeds projector system alignment.
    int leftBound = bottomRightY;
    int rightBound = topLeftY;
    int upperBound = topLeftX;
    int lowerBound = bottomRightX;
    
    JSONObject currBoundCoords = new JSONObject();
    
    currBoundCoords.setInt("left_bound", leftBound);
    currBoundCoords.setInt("right_bound", rightBound);
    currBoundCoords.setInt("upper_bound", upperBound);
    currBoundCoords.setInt("lower_bound", lowerBound);


    panels.add(new Panel(i, 0, 0, black));
    boundaryCoords.setJSONObject(i, currBoundCoords);
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
    
    int currLeftBoundary = boundaryCoords.getJSONObject(0).getInt("left_bound");
    int currRightBoundary = boundaryCoords.getJSONObject(0).getInt("right_bound");
    int currLowerBoundary = boundaryCoords.getJSONObject(0).getInt("lower_bound");
    int currUpperBoundary = boundaryCoords.getJSONObject(0).getInt("upper_bound");
  
  int circleR = (currLowerBoundary - currUpperBoundary) / 7;
  
  int circleY = currLeftBoundary + ((currRightBoundary - currLeftBoundary) / 2);
  
  int xMultiplier = (currLowerBoundary - currUpperBoundary) / (numFactors + 1);
  int circleX = currUpperBoundary + (xMultiplier * (yInd + 1));
  
  PVector loc = new PVector(circleX, circleY);
  PVector vel = new PVector(0, initialVelocity);
  PVector g = new PVector(0, initialGravity);
  
  
  int currPanel = 0;

  Panel currPanelObj = panels.get(currPanel);
  if (identity == "male") {
    currPanelObj.maleCount += 1;
  } else if (identity == "female") {
    currPanelObj.femaleCount += 1;
  }
  
  float maleFemaleProportion = floor(float(currPanelObj.femaleCount) / float(currPanelObj.maleCount + currPanelObj.femaleCount) * 8);
  currPanelObj.backgroundColor = pinkBlueColorGradient[int(maleFemaleProportion)];
  
  GCircle currCircle = new GCircle(circleCount, circleX, circleY, circleR, currPanel, fc, identity, loc, vel, g);
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

    if ((location.y < (currLeftBound + (circleR / 2))) || (location.y > (currRightBound + (circleR / 2)))) {
      if (bounceCount == 0 && currPanel != 0){
        // TODO: this is hacky, can i fix?
        //velocity.y = -10.799994;
        if (currPanel != 2 && currPanel != 3) {
          velocity.y = velocity.y / 1.5;
        } else {
          velocity.y = velocity.y / 1.2;
        }
      }
      velocity.y = velocity.y * -0.97;
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
    if (circleCount >= 200) {
      gCircles.clear();
      circleCount = 0;
      delay(500);
      addCircle("male");
      addCircle("female");
    }
    if (currPanel < boundaryCoords.size()) {
      int prevLowerBoundary = boundaryCoords.getJSONObject(currPanel - 1).getInt("lower_bound");
      int prevUpperBoundary = boundaryCoords.getJSONObject(currPanel - 1).getInt("upper_bound");
      
      int currLowerBoundary = boundaryCoords.getJSONObject(currPanel).getInt("lower_bound");
      int currUpperBoundary = boundaryCoords.getJSONObject(currPanel).getInt("upper_bound");
            
      int maleFemale = id == "female" ? 1 : 2;
      
      location.y = boundaryCoords.getJSONObject(currPanel).getInt("right_bound");
      location.x = currUpperBoundary + (((currLowerBoundary  - currUpperBoundary) / (numFactors + 1)) * maleFemale);
      
      velocity.y = initialVelocity;
      gravity.y = initialGravity;
      bounceCount = 0;


      Panel prevPanelObj = panels.get(currPanel - 1);
      
      if (id == "male") {
        prevPanelObj.maleCount -= 1;
      } else if (id == "female") {
        prevPanelObj.femaleCount -= 1;
      }
      
      float prevMaleFemaleProportion = floor(float(prevPanelObj.femaleCount) / float(prevPanelObj.maleCount + prevPanelObj.femaleCount) * 8);
      prevPanelObj.backgroundColor = pinkBlueColorGradient[int(prevMaleFemaleProportion)];
  
      
      Panel currPanelObj = panels.get(currPanel);
      if (id == "male") {
        currPanelObj.maleCount += 1;
      } else if (id == "female") {
        currPanelObj.femaleCount += 1;
      }
      
      float maleFemaleProportion = floor(float(currPanelObj.femaleCount) / float(currPanelObj.maleCount + currPanelObj.femaleCount) * 8);
      currPanelObj.backgroundColor = pinkBlueColorGradient[int(maleFemaleProportion)];
      
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
        panelStat = toCollege.get(identity);
        break;
      case 2:
        panelStat = toEntryLevel.get(identity);
        break;
      case 3:
        panelStat = toSeniorLevel.get(identity);
        break;
      case 4:
        panelStat = toExecLevel.get(identity);
        println("becoming execs");
        break;
      case 5:
        println("all done");
        panelStat = -1;
        break;
    }
    
    return panelStat;
  }
}

class Panel {
  int index;             // the index of the panel
  int maleCount;         // the blue/male circle count
  int femaleCount;       // the pink/female circle count
  color backgroundColor; //the background color of the panel
  
  Panel(int i, int mc, int fc, color bc) {
    index = i;
    maleCount = mc;
    femaleCount = fc;
    backgroundColor = bc;
  }
}
