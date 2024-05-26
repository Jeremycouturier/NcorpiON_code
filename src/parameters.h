/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/******** @file    parameters.h                                                ********/
/******** @brief   Main header file. The user who does not modify NcorpiON     ********/
/********          shall only modify this file                                 ********/
/******** @author  Jérémy COUTURIER <jeremycouturier.com>                      ********/
/********                                                                      ********/
/******** @section 	LICENSE                                                ********/
/******** Copyright (c) 2023 Jérémy COUTURIER                                  ********/
/********                                                                      ********/
/******** This file is part of NcorpiON                                        ********/
/********                                                                      ********/
/******** NcorpiON is free software. You can redistribute it and/or modify     ********/
/******** it under the terms of the GNU General Public License as published by ********/
/******** the Free Software Foundation, either version 3 of the License, or    ********/
/******** (at your option) any later version.                                  ********/
/********                                                                      ********/
/******** NcorpiON is distributed in the hope that it will be useful,          ********/
/******** but WITHOUT ANY WARRANTY; without even the implied warranty of       ********/
/******** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         ********/
/******** GNU General Public License for more details.                         ********/
/********                                                                      ********/
/******** You should have received a copy of the GNU General Public License    ********/
/******** along with NcorpiON.  If not, see <http://www.gnu.org/licenses/>.    ********/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/


#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_



/**************************************************************************************************/
/******** Defining the input/output path where data are output if write_to_files_bool is 1 ********/
/******** and where initial conditions are read if random_initial_bool is 0                ********/
/******** Put / at the end of the path. The path must exist and be absolute.               ********/
/**************************************************************************************************/

#define pth "/home/user/Documents/NcorpiON/"



/**************************************************************************/
/******** Defining booleans to determine the behaviour of NcorpiON ********/
/**************************************************************************/

/******** General booleans relative to the simulation ********/
#define write_to_files_bool      0   //Determines if the simulation writes to output files. Set to 0 to run speed tests, or if you are satisfied with what is displayed in the terminal
                                     //You can also set this boolean to 0 if you only want to 3D visualize the simulation in your browser.
#define make_animation_bool      0   //Determines if animations of the simulation are produced. write_to_files_bool and write_elliptic_bool must both be set to 1
#define write_cartesian_bool     0   //Determines if the cartesian elements x, y, z, vx, vy, vz   should be output. Unimportant if write_to_files_bool is 0. Output in simulation's units
#define write_elliptic_bool      1   //Determines if the elliptic  elements a, lambda, k, h, q, p should be output. Unimportant if write_to_files_bool is 0. Output in simulation's units
                                     //If write_to_files_bool is 1 but both write_cartesian_bool and write_elliptic_bool are 0, then only radius.txt, mass.txt and stat.txt are output
#define central_mass_bool        1   //Determines if there is a central mass. If 0, none of the bodies in the simulation play any particular role. If 1, the central body is initially
                                     //at (x,y,z,vx,vy,vz) = {0.0} and treated independently. Should be set to 1 if one body is very massive and if brute_force_bool is 0, so gravity
                                     //with that body is computed directly and not from a tree or a mesh. If 1, some physical effects can be considered as well(see below).
#define reduce_to_COM_bool       1   //Determines if the position and speed of the center of mass of the system are cancelled by a translation before simulating. If 0, then the center
                                     //of mass will drift linearly with time, which could be a problem due to the limit of floating-point representation. Setting to 1 is recommended.
                                     //Note that the position and speed of the central body (if any) will slightly deviate from 0 after the reduction of the center of mass.
#define random_initial_bool      1   //Determines if the initial conditions are drawn randomly between bounds defined below. If 0, the initial conditions are read from the file init.txt
                                     //located at the path defined above, with one line per body and 8 columns, the first six for the initial conditions and the last two for mass and
                                     //radius (in simulation unit). If central_mass_bool is 1 and random_initial_bool is 0, do not include the central body in init.txt.
#define initial_cartesian_bool   1   //Determines if the initial conditions are given in cartesian coordinates (X,Y,Z,vX,vY,vZ). If 0, then the initial conditions are (semi-major axis,
                                     //eccentricity, inclination, true anomaly, argument of periapsis, longitude of ascending node). Unimportant if random_initial_bool is 1.
                                     //The initial conditions in the file init.txt must be given in simulation's units and radians.
#define seed_bool                1   //Determines if the seed for random number generation is chosen by the user. If seed_bool is 0, the seed is the number of seconds since 01/01/1970
#define one_collision_only_bool  0   //Determines if bodies are only allowed to collide once per timestep. If 0, there is no restriction on the number of collisions a body can experience
                                     //during a timestep. Setting first to 1 and then to 0 is a good way to know if the timestep is adapted to the bodies' mean free path.
#define openGL_bool              0   //Determines if a 3D real-time visualization of the simulation is enabled. You must match openGL_bool to the same value in the makefile
#define resume_simulation_bool   0   //Determines if, at the end of the simulation, NcorpiON generates a file named init.txt that can be used to resume the simulation. The file init.txt
                                     //is stored at the path indicated above. To resume the simulation, you need to set random_initial_bool to 0, initial_cartesian_bool to 1, and N_0 to
                                     //the number of lines of init.txt. If init.txt already exists in path pth, it will be overwritten. Simulation's variables should be updated.

/******** Booleans relative to interactions with the central mass or a distant object. Set to 0 if central_mass_bool is 0 ********/
#define J2_bool                  0   //Determines if the contribution from the J2 is taken into account in the simulation. The (x,y) plane of the simulation must be the equatorial plane
#define Sun_bool                 0   //Determines if the perturbations from a distant object that the system orbits (or is orbited by) are taken into account in the simulation
#define central_tides_bool       0   //Determines if orbiting bodies raise tides on the central body. The tidal model used by NcorpiON is the constant timelag model
#define inner_fluid_disk_bool    0   //Determines if there is an inner fluid disk (disk of liquid material below the Roche radius from which bodies spawn). See Salmon & Canup 2012
                                     //If set to 1, its mass is added to that of the central body when computing gravitational interactions and when preserving the total momemtum

/******** Booleans relative to mutual interactions between the bodies ********/
#define collision_bool           1   //Determines if the bodies are able to collide. If 0, the bodies pass through each other and you should set a non-zero value for softening_parameter
#define mutual_bool              1   //Determines if there is mutual gravity between the bodies. If central_mass_bool is 1, the bodies interact with the central mass even if set to 0.

/******** Booleans relative to the treatment of mutual interactions (collisions and self-gravity). Exactly one of them must be 1. Unimportant if mutual_bool is 0 ********/
#define brute_force_bool         0   //Determines if a brute-force method should be used for mutual interactions.
#define falcON_bool              1   //Determines if falcON algorithm     should be used for mutual interactions. (Best speed/accuracy compromise for large N + preserve total momentum)
#define standard_tree_bool       0   //Determines if a standard tree code should be used for mutual interactions. (Much slower than falcON for the same accuracy, momentum not preserved).
#define mesh_bool                0   //Determines if the  mesh algorithm  should be used for mutual interactions. (Fastest but gravity with neighbours and three largest bodies only).

/******** Booleans relative to collision resolution. Exactly one of them must be 1. Unimportant if collision_bool is 0 ********/
#define elastic_collision_bool   0   //Determines if the collisions are all elastic.
#define inelastic_collision_bool 0   //Determines if the collisions are all inelastic with inelasticity parameter collision_parameter.
#define instant_merger_bool      0   //Determines if the collisions all result in a merger.
#define fragmentation_bool       1   //Determines if the outcome of the collision should be either a merge, a partial fragmentation, a full fragmentation, or a catastrophic disruption,
                                     //depending on the relative velocity. Set to 1 to use the fragmentation model of NcorpiON.
                                     
                                     

/**************************************************/
/******** Defining some physical constants ********/
/**************************************************/

/******** Defining a system of units for the simulation. If random_initial_bool is 0, then the units in the file init.txt must be the simulation's units ********/
#define R_unit 1.0                   //If central_mass_bool is 1, then radius of the central body. Otherwise, unimportant for the simulation. You define your own unit of length.
#define M_unit 1.0                   //If central_mass_bool is 1, then   mass of the central body. Otherwise this is the mass for conversions cartesian <-> elliptic
#define G 39.47841760435743          //The gravitational constant. It is here set to 4*pi^2, so that a body of semi-major axis 1 orbiting a mass 1 has a period 1
                                     //Note that R_unit and M_unit do not necessarily have to be 1, they should just be equal to the mass and radius of the central body in the system
                                     //of units that you want to use for the simulation. It is generally advised to use a system of units such that the simulation will not have to
                                     //manipulate absurdely large or small floating points numbers. If central_mass_bool is 0, then you don't have to define R_unit and you should define
                                     //M_unit as the mass, in your system of units, that is used to convert cartesian coordinates into elliptic coordinates. Whether central_mass_bool
                                     //is 0 or 1, you have to define G as the value of the gravitational constant in your system of units. Even if the mass of the central body changes,
                                     //M_unit stays the mass used for conversions cartesian <-> elliptic.

/******** Physical constants relative to interactions with the central body (J2, inner disk, central tides) or a distant object. Unimportant if central_mass_bool is 0 ********/
#define Tearth 3.4076                //Central body's sideral period in units of the surface orbital period. Must be > 1. Earth's current value is 17.038
                                     //In case of tides, the sideral period changes and this is the value at t = 0.
#define J2_value 0.0                 //The J2 of the central body. If you choose J2_value = 0.0, then J2 is obtained from J2 = 1/2*Omega^2/Omega_crit^2 (fluid body)
                                     //where Omega is the sideral frequency and Omega_crit = sqrt(G*M_unit/R_unit^3)
#define k2 1.5                       //Second Love number of the central body. Here the value is for a fluid body (zero shear modulus). The constant timelag model is used
#define Delta_t 0.0002428            //The timelag between stress and response. Here 10 minutes. In units of the orbital period at the surface of the central body.
#define dimensionless_moi 0.3307     //The moment of inertia of the central body, in simulation units (in units of its mass times its radius squared).
#define star_semi_major 23481.066    //The semi-major axis of the orbit of the system around the distant object in simulation units.
#define star_mass 332946.0434581987  //The mass of the distant object in simulation units.
#define obliquity 0.0                //The angle between the simulation's reference plane and the orbit of the distant object.
#define inner_mass 0.014             //Mass of the inner fluid disk at t = 0.
#define spawned_density 0.1448       //Density of the bodies that spawn from the inner fluid disk, in simulation's units.
#define f_tilde 0.3                  //A parameter controlling the mass of bodies spawned from the inner fluid disk. Must be < 1. Salmon & Canup (2012) choose 0.3
#define Rroche 2.9                   //The Roche radius where bodies spawn from the inner fluid disk (in simulation's units). The radius of tidal disruption is low_dumping_threshold
                                     //defined below. Must be larger than both low_dumping_threshold and than R_unit.



/*******************************************************/
/******** Parameters relative to the simulation ********/
/*******************************************************/

/******** General parameters ********/
#define N_max 15000                  //Maximum number of bodies that the simulation can handle. The simulation will stop if the number of bodies ever exceeds N_max.
#define N_0 1000                     //Initial number of bodies, central body excluded (if any). Must be less than N_max. If random_initial_bool is 0, number of lines of init.txt
#define t_end 256.0                  //Total simulation length    (in simulation's units)
#define time_step 0.015625           //Timestep of the simulation (in simulation's units)
#define output_step 32               //Output occurs every output_step timestep. Unimportant if write_to_files_bool is 0
#define low_dumping_threshold 2.0    //Threshold (in simulation's units) below  which bodies are dumped from the simulation. Unimportant if central_mass_bool is 0.
#define high_dumping_threshold 128.0 //Threshold (in simulation's units) beyond which bodies are dumped from the simulation (assumed unbounded)

/******** Specific parameters ********/
#define max_ids_per_node 173         //The maximum number of ids in each node of the unrolled linked lists (chains). Choose such that sizeof(struct chain) be a multiple of the cache line
#define softening_parameter 0.0      //The softening parameter for mutual gravitational interations, in units of the sum of the radii.
#define seed 129425372               //The seed used for random number generation. Unimportant if seed_bool is 0.
#define switch_to_brute_force 0      //Threshold for N below which the program switches to the brute-force method for mutual interactions. Unimportant if brute_force_bool is 1

/******** Bounds for initial conditions. Unimportant if random_initial_bool is 0. The initial conditions are drawn uniformly at random between these bounds ********/
#define radius_min 0.01              //Minimal radius                   of a body at t = 0
#define radius_max 0.06              //Maximal radius                   of a body at t = 0
#define density_min 0.1448           //Minimal density                  of a body at t = 0
#define density_max 0.1448           //Maximal density                  of a body at t = 0
#define eccentricity_min 0.0         //Minimal eccentricity             of a body at t = 0
#define eccentricity_max 0.2         //Maximal eccentricity             of a body at t = 0
#define sma_min 2.9                  //Minimal semi-major axis          of a body at t = 0
#define sma_max 14.0                 //Maximal semi-major axis          of a body at t = 0
#define inclination_min 0.0          //Minimal inclination (in radians) of a body at t = 0
#define inclination_max 0.174533     //Maximal inclination (in radians) of a body at t = 0
                                     //The true longitude, argument of pericenter and longitude of the ascending node are drawn uniformly at random between 0 and 2*M_PI
                                     //These bounds must be defined in the simulation's units
                                     
/******** Parameters relative to 3D visualization with REBOUND. Unimportant if openGL_bool is 0 ********/
#define browser_port 1234            //The http port where your browser will communicate with REBOUND. You can visualize several simulations at the same time if you change the port
#define radius_blow_up_factor 4.0    //All the bodies, except the central mass (if any), are displayed with a radius that much larger than their true radius. Can enhance visualization

/*************************************************************************************************************************/
/******** Parameters relative to tree-based algorithms (falcON and the standard tree code). If either falcON_bool ********/
/******** or standard_tree_bool is 1, then Dehnen's falcON algorithm or Barnes & Hut's standard tree code is used ********/
/******** to compute mutual gravity and to detect collisions. In theses cases, these parameters must be defined   ********/
/*************************************************************************************************************************/

#define expansion_order 3            //The order p of the Taylor expansions. This is p = 3 in Dehnen (2002). NcorpiON allows up to p = 6. Minimum is 1 as order 0 yields no acceleration
#define theta_min 0.5                //Minimal value of the tolerance parameter theta. Must be strictly less than 1. Sensible values are 0.2 < theta_min < 0.8
                                     //The precision (and computational time) of the mutual gravity computed by Ncorpion increases with increasing p and decreasing theta_min.
#define subdivision_threshold 17     //A cubic cell is not divided as long as it contains at most that many bodies. Called s in Dehnen (2002). Must be > 0. The precision does not depend
                                     //on this threshold, but the computational time does. Suggested values are 5 < s < 200 but must be tweaked by the user to obtain the best performances
#define root_sidelength 128.0        //Sidelength of the root cell (in simulation's units). Should be machine representable. Particles outside of the root cell don't feel others.
#define level_max 25                 //The maximum allowed number of levels in the tree. Root is at level 0 and a cell at level level_max - 1 is never divided.
#define child_multipole_threshold 1  //If number of bodies/number of children is at most this threshold then the multipole moments of a cell are computed directly from the bodies.
                                     //Otherwise, they are computed from that of the children

/******** Parameters specifically relative to mutual gravity computation with falcON algorithm ********/
#define N_cc_pre 8                   //For two cells with N1 and N2 bodies, if N1N2 < N_cc_pre, then the interaction is computed brute-forcely, regardless of their well-separation
#define N_cc_post 64                 //For two cells with N1 and N2 bodies, if N1N2 < N_cc_post and they are not well-separated, then the interaction is computed brute-forcely
#define N_cs 64                      //If N1 < N_cs, then the self-interaction of a cell containing N1 bodies is computed brute-forcely
                                     //See TreeWalk algorithm in the paper for details about these thresholds. The precision does not depend on these thresholds, but the computational
                                     //time slightly does. However, note that the computational cost depends much more on the subdivision threshold s that on these thresholds. Suggested
                                     //values are (s, N_cc_pre, N_cc_post, N_cs) = (26, 8, 64, 64) for p = 3 and (s, N_cc_pre, N_cc_post, N_cs) = (80, 256, 1024, 128) for p = 6 but this
                                     //depends on the architecture and should be tweaked. N_cc_post must be larger that N_cc_pre.
                                     
/******** Parameters specifically relative to mutual gravity computation with the standard tree code ********/
#define N_cb_pre 6                   //If N1 < N_cb_pre, the interaction between a body and a cell with N1 bodies is performed brute-forcely, regardless of their well-separation
#define N_cb_post 16                 //If N1 < N_cb_post and they are not well-separated, the interaction between a body and a cell with N1 bodies is performed brute-forcely.

/******** Parameters specifically relative to collision detection with falcON algorithm ********/
#define N_cc_collision 16            //This is N_cc_post. For two nodes not well-separated with Na and Nb bodies, if NaNb < N_cc_collision, then collisions are searched brute-forcely,
                                     //otherwise, the largest node is subdivised. N_cc_pre is always 0 when falcON is used for collision detection and is not a parameter
#define N_cs_collision 12            //For a node with Na bodies, if Na < N_cs_collision, then collisions are searched brute-forcely, otherwise, the node is subdivised

/******** Parameters specifically relative to collision detection with the standard tree code ********/
#define N_cb_collision 16            //This is N_cb_post. For a body not well-separated from a node with Na bodies, if Na < N_cb_collision, then collisions are searched brute-forcely,
                                     //otherwise, the node is subdivised. N_cb_pre is always 0 when the standard tree code is used for collision detection and is not a parameter
                                     
                                     
                                     
/*****************************************************************************************************************/
/******** Parameters relative to the mesh-grid algorithm. If mesh_bool is 1 then a mesh algorithm is used ********/
/******** to compute mutual gravity and detect collisions. In that case, these parameters must be defined ********/
/*****************************************************************************************************************/

#define collision_cube_min 80.0      //Minimal sidelength of the mesh-grid (in simulation's units). The mesh-size will never be less than collision_cube_min/collision_cube_cells
#define collision_cube_cells 1024    //Number of mesh cells per dimension of the collision cube. Must be even. For 16+ GiB of RAM (resp. 8 or 4 GiB), choose ~1000 (resp. ~800 or ~500)
#define how_many_neighbours 16.0     //The desired expected number of neighbours for a body



/*****************************************************************************************/
/******** Parameters relative to collision resolution and the fragmentation model ********/
/*****************************************************************************************/

/******** Collision resolution when all collisions are inelastic. Important only if both collision_bool and inelastic_collision_bool are 1 ********/
#define collision_parameter 1.0      //The collision parameter f to model inelastic collision. Must be between 1 (completely inelastic) and 2 (elastic)

/******** Collision resolution with the fragmentation model described in NcorpiON's paper. Important only if both collision_bool and fragmentation_bool are 1 ********/
#define N_tilde 15                   //Ratio between ejected mass and mass of the second largest fragment : N° of fragments in the tail. 2*beta/(3-beta) in Leinhardt & Stewart(2012)
#define mu_parameter 0.55            //The exponent of the impact velocity in the coupling parameter. See Table 3 of Housen & Holsapple (2011)
#define nu_parameter 0.4             //The exponent of the density         in the coupling parameter. See Table 3 of Housen & Holsapple (2011)
#define C1_parameter 1.5             //A dimensionless parameter of impact theories. See Table 3 of Housen & Holsapple (2011)
#define k_parameter 0.2              //A dimensionless parameter of impact theories. See Table 3 of Housen & Holsapple (2011)
#define frag_threshold 0.00000002    //Ejected mass threshold below which the collision results in a merger. If the ejected mass is above that threshold but the mass of the second
                                     //largest fragment is below, then the tail is reunited into a single body. If the mass of the second largest fragment is above that threshold
                                     //then the collision results in a full fragmentation. To be given in simulation's units
#define pq_min_max {-1,3,-1,1}       //Extremal integer values for p_k and q_k to determine the position of the tail fragments with respect to the largest fragment.
                                     //Must define a rectangle containing exactly N_tilde points with integer coordinates. More precisely, if pq_min_max = {a, b, c, d},
                                     //then we must have N_tilde = (b - a + 1)*(d - c + 1). See NcorpiON's paper for details
                                     


/*********************************************************/
/******** Redefining keywords. Not to be modified ********/
/*********************************************************/

#define typ double                   //Renaming double as typ
#define MPI_TYP MPI_DOUBLE           //Renaming double as typ for mpi
#define bigint long int              //Renaming long int as bigint. If sizeof(int) == sizeof(long int) == 4 on your system, then define bigint as long long int instead
                                     //Open the file /usr/share/gtksourceview/language-specs/c.lang and then find the field
                                     //<context id="types" style-ref="type">. Add the lines <keyword>typ</keyword> and <keyword>bigint</keyword> to it
                                     //and color gedit with C. The keywords typ and bigint should now be colored after a reboot
#define type_check __builtin_types_compatible_p 



#endif
