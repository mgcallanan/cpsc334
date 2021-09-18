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

int femaleColor = color(180, 43, 106);
int maleColor = color(136, 196, 230);

color [] circleColors = {femaleColor, maleColor};
String [] ids = {"female", "male"};

// ArrayList of all the generated circles
ArrayList<GCircle> gCircles;

// JSONArray to store boundary coords of the screens
JSONArray boundaryCoords;

void settings() {  
  size(screenWidth, screenHeight);
}

void setup() {
    boundaryCoords = new JSONArray();
    gCircles = new ArrayList<GCircle>();
    
    for (int i = 0; i < numRects; i++) {
      int boundaryX = xMultiplier * i;
      
      JSONObject currBoundCoords = new JSONObject();
      
      currBoundCoords.setInt("left_bound", boundaryX);
      currBoundCoords.setInt("right_bound", boundaryX + xMultiplier);
      currBoundCoords.setInt("upper_bound", 0);
      currBoundCoords.setInt("lower_bound", screenHeight);
      
      boundaryCoords.setJSONObject(i, currBoundCoords);
    }
    
    println(boundaryCoords);
     // TODO: MOVE THIS OUT OF DRAW
    initCircles();
}


void draw() {
    background(0, 0, 0);
    
    for (int i = 0; i < numRects; i++) {
      stroke(255, 255, 255);
      int currBoundaryX = boundaryCoords.getJSONObject(i).getInt("left_bound");
      line(currBoundaryX, 0, currBoundaryX, screenHeight);
    }

    for (int i = 0; i <= gCircles.size() - 1; i++) {
      GCircle gCircle = gCircles.get(i);
      gCircle.move();
      gCircle.display();
    }
    
        
}

// Function to create circles in first stage
void initCircles() {
  
  for (int i = 0; i < numFactors; i++) {
      int circleX = boundaryCoords.getJSONObject(0).getInt("left_bound") + (xMultiplier / 2);
      int circleY = boundaryCoords.getJSONObject(0).getInt("upper_bound") + (yMultiplier * (i + 1));
      
      PVector loc = new PVector(circleX, circleY);
      PVector vel = new PVector(1, 0);
      PVector g = new PVector(0.2, 0);
      
      int currPanel = 0;
      
      GCircle currCircle = new GCircle(circleX, circleY, circleRadius, currPanel, circleColors[i], ids[i], loc, vel, g);
      gCircles.add(currCircle);
  }
  
}

// Class for the generated circles
class GCircle {
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
  
  GCircle(float ix, float iy, float cr, int cp, color fc, String identity, PVector loc, PVector vel, PVector g) {
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
      velocity.x = velocity.x * -0.97;
      bounceCount++;
      println(bounceCount);
    }
  }
  
}
  