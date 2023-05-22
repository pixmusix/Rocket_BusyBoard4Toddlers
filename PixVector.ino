/*
  Loosely based on the work of Dan Shiffman, Ben Fry, and Casey Reas
 */

#include <math.h> 

class PVector {

  public:

    /** The x component of the vector. */
    float x;

    /** The y component of the vector. */
    float y;


  /**
   * Constructor for an empty vector: x, y, and z are set to 0.
   */
  PVector() {
  }

  PVector(float a, float b) {
    x = a;
    y = b;
  }


  /**
   * Set x, y, and z coordinates.
   */
  void set(float a, float b) {
    x = a;
    y = b;
  }


  /**
   * Set x, y, and z coordinates from a Vector3D object.
   */
  void set(PVector v) {
    x = v.x;
    y = v.y;
  }

  /**
   * Calculate the magnitude (length) of the vector
   */
  float mag() {
    return sqrt(x*x + y*y);
  }


  /**
   * Add a vector to this vector
   */
  void add(PVector v) {
    x += v.x;
    y += v.y;
  }


  void add(float a, float b) {
    x += a;
    y += b;
  }

  /*
   * Subtract a vector from this vector
   * @param v the vector to be subtracted
   */
  void sub(PVector v) {
    x -= v.x;
    y -= v.y;
  }


  void sub(float a, float b) {
    x -= a;
    y -= b;
  }

  /**
   * Multiply this vector by a scalar
   */
  void mult(float n) {
    x *= n;
    y *= n;
  }


  /**
   * Multiply each element of one vector by the elements of another vector.
   */
  void mult(PVector v) {
    x *= v.x;
    y *= v.y;
  }

  /**
   * Divide this vector by a scalar
   */
  void div(float n) {
    x /= n;
    y /= n;
  }

  /**
   * Divide each element of one vector by the elements of another vector.
   */
  void div(PVector v) {
    x /= v.x;
    y /= v.y;
  }

  /**
   * Calculate the Euclidean distance between two points (considering a point as a vector object)
   */
  float dist(PVector v) {
    float dx = x - v.x;
    float dy = y - v.y;
    return sqrt(dx*dx + dy*dy);
  }


  /**
   * Calculate the Euclidean distance between two points (considering a point as a vector object)
   */
  static float dist(PVector v1, PVector v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return sqrt(dx*dx + dy*dy);
  }


  /**
   * Calculate the dot product with another vector
   */
  float dot(PVector v) {
    return x*v.x + y*v.y;
  }


  float dot(float a, float b) {
    return x*a + y*b;
  }
  
  
  static float dot(PVector v1, PVector v2) {
      return v1.x*v2.x + v1.y*v2.y;
  }

  /**
   * Normalize the vector to length 1 (make it a unit vector)
   */
  void normalize() {
    float m = mag();
    if (m != 0 && m != 1) {
      div(m);
    }
  }

  /**
   * Limit the magnitude of this vector
   */
  void limit(float max) {
    if (mag() > max) {
      normalize();
      mult(max);
    }
  }


  /**
   * Calculate the angle of rotation for this vector
   */
  float heading2D() {
    float angle = (float) atan2(-y, x);
    return -1*angle;
  }


  /**
   * Calculate the angle between two vectors, using the dot product
   */
  static float angleBetween(PVector v1, PVector v2) {
    double dot = v1.x * v2.x + v1.y * v2.y;
    double v1mag = sqrt(v1.x * v1.x + v1.y * v1.y);
    double v2mag = sqrt(v2.x * v2.x + v2.y * v2.y);
    return (float) acos(dot / (v1mag * v2mag));
  }
};

