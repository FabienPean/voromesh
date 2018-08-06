#include <igl/opengl/glfw/Viewer.h>
#include <voro++/voro++.hh>

using namespace voro;

// This function returns a random floating point number between 0 and 1
double rnd() {return double(rand())/RAND_MAX;}

int main(int argc, char *argv[])
{
    	double x,y,z,rsq,r;
	voronoicell v;

	// Initialize the Voronoi cell to be a cube of side length 2, centered
	// on the origin
	v.init(-1,1,-1,1,-1,1);

	// Cut the cell by 250 random planes which are all a distance 1 away
	// from the origin, to make an approximation to a sphere
	for(int i=0;i<250;i++) {
		x=2*rnd()-1;
		y=2*rnd()-1;
		z=2*rnd()-1;
		rsq=x*x+y*y+z*z;
		if(rsq>0.01&&rsq<1) {
			r=1/sqrt(rsq);x*=r;y*=r;z*=r;
			v.plane(x,y,z,1);
		}
	}

	// Output the Voronoi cell to a file, in the gnuplot format
	v.draw_gnuplot(0,0,0,"single_cell.gnu");
    
  // Inline mesh of a cube
  const Eigen::MatrixXd V= (Eigen::MatrixXd(8,3)<<
    0.0,0.0,0.0,
    0.0,0.0,1.0,
    0.0,1.0,0.0,
    0.0,1.0,1.0,
    1.0,0.0,0.0,
    1.0,0.0,1.0,
    1.0,1.0,0.0,
    1.0,1.0,1.0).finished();
  const Eigen::MatrixXi F = (Eigen::MatrixXi(12,3)<<
    1,7,5,
    1,3,7,
    1,4,3,
    1,2,4,
    3,8,7,
    3,4,8,
    5,7,8,
    5,8,6,
    1,5,6,
    1,6,2,
    2,6,8,
    2,8,4).finished().array()-1;
    
    

  // Plot the mesh
  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(V, F);
  viewer.data().set_face_based(true);
  viewer.launch();
}
