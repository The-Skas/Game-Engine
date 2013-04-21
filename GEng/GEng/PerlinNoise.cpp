#include "PerlinNoise.h"

void PerlinNoise::Initialise()
{

  RandomVectors = new float**[length];
  rateOfChange =  new float**[length];
  for (unsigned i = 0; i < length; ++i)
  {
    RandomVectors[i] = new float*[width];
    rateOfChange[i] =  new float*[width];
    for (unsigned j = 0; j < width; ++j)
    {
      RandomVectors[i][j] = new float[2];
      rateOfChange[i][j]  = new float[2];

      //Intialise Each Segment to have a random vector: X = [0] , Y = [1]
      RandomVectors[i][j][0] = sf::Randomizer::Random(-1.0f, 1.0f);
      RandomVectors[i][j][1] = sf::Randomizer::Random(-1.0f, 1.0f);

      rateOfChange[i][j][0] = sf::Randomizer::Random(-1.0f, 1.0f);
      rateOfChange[i][j][1] = sf::Randomizer::Random(-1.0f, 1.0f);

      float distance = Distance(rateOfChange[i][j][0],rateOfChange[i][j][1]);

      rateOfChange[i][j][0] /= distance*rateofchange;
      rateOfChange[i][j][1] /= distance*rateofchange;
    

    }
  }


};

//Math Functions Coordinate systems always obey the natural coordinate system as in
//ie: As Y UP is Positive, X RIght is positive
 void PerlinNoise::Update()
{
  
  
};

float PerlinNoise::Perlin2D(float rndmX, float rndmY)
{

  //Floor the X, Y values to get the appropiate grid.

  float xwidth = (std::floor(rndmX));
  float ylength =(std::floor(rndmY));
  
  //Get the values of the 4 grid points that surround the X, Y values.
 /* float topLeftX = RandomVectors[(int)xwidth][(int)ylength][0];
  float topLeftY = RandomVectors[(int)xwidth][(int)ylength][1];

  float topRightX = RandomVectors[(int)xwidth+1][(int)ylength][0];
  float topRightY = RandomVectors[(int)xwidth+1][(int)ylength][1];

  float botRightX = RandomVectors[(int)xwidth+1][(int)ylength+1][0];
  float botRightY = RandomVectors[(int)xwidth+1][(int)ylength+1][1];

  float botLeftX =  RandomVectors[(int)xwidth][(int)ylength+1][0];
  float botLeftY =  RandomVectors[(int)xwidth][(int)ylength+1][1];*/

  //Measure the vector from the X,Y values to the grid point.
  float xToLeft = xwidth-rndmX;
  float xToRight = xwidth+1-rndmX;

  //By flipping these too assignments, it fixed the unalignment. Why?
  //Since i created the grid assignments X-> Positive, And y positive is below.
  //So it has to follow that rule.
  float yToTop = ylength - rndmY;
  float yToBot = ylength+1 - rndmY;

  //Top Left
  float DotTopL = DotProduct(xToLeft, yToTop, RandomVectors[(int)xwidth][(int)ylength][0], RandomVectors[(int)xwidth][(int)ylength][1]);

  float DotBotL = DotProduct(xToLeft, yToBot, RandomVectors[(int)xwidth][(int)ylength+1][0], RandomVectors[(int)xwidth][(int)ylength+1][1]);

  float DotTopR = DotProduct(xToRight, yToTop,RandomVectors[(int)xwidth+1][(int)ylength][0],RandomVectors[(int)xwidth+1][(int)ylength][1]);

  float DotBotR = DotProduct(xToRight, yToBot, RandomVectors[(int)xwidth+1][(int)ylength+1][0],RandomVectors[(int)xwidth+1][(int)ylength+1][1]);

  float topInterpolate = LERP(DotTopL, DotTopR, rndmX-xwidth);
 
  float botInterpolate = LERP(DotBotL, DotBotR, rndmX-xwidth);

  float topBotInterpolate = LERP(topInterpolate, botInterpolate, rndmY-ylength);
  

  float tempX, tempY;
  tempX = RandomVectors[(int)xwidth][(int)ylength][0];
  tempY = RandomVectors[(int)xwidth][(int)ylength][1];
  float rndm1, rndm2;
  rndm1 = sf::Randomizer::Random(-1.0f, 1.0f);
  rndm2 = sf::Randomizer::Random(-1.0f, 1.0f);
  

  RandomVectors[(int)xwidth][(int)ylength][0] += -rateOfChange[(int)xwidth][(int)ylength][0]/1000.0f;
  
  RandomVectors[(int)xwidth][(int)ylength][1] +=  -rateOfChange[(int)xwidth][(int)ylength][1]/1000.0f;


  if (RandomVectors[(int)xwidth][(int)ylength][0] > 1 || RandomVectors[(int)xwidth][(int)ylength][0] < -1
   || RandomVectors[(int)xwidth][(int)ylength][1] > 1 || RandomVectors[(int)xwidth][(int)ylength][1] < -1)
  {
    rateOfChange[(int)xwidth][(int)ylength][0] *= -1;
    rateOfChange[(int)xwidth][(int)ylength][1] *= -1;

  }




  return topBotInterpolate;
  //Dotproduct each vector with its appropriate corner gradiant value.
  //This will leave you with four values for each corner of the grid.
  //Now with these 4 values, we will be able to interpolate what the X/Y point's
  //value should be. And Finally it returns the PerlinNoise at that point.
};

PerlinNoise::~PerlinNoise()
{
  for (unsigned i = 0; i < length; ++i)
  {
    for (unsigned j = 0; j < width; ++j)
    {
      delete  &(RandomVectors[i][j][0]);
      delete  &(RandomVectors[i][j][1]);

      delete  &(rateOfChange[i][j][0]);
      delete  &(rateOfChange[i][j][1]);
    }
  }
}