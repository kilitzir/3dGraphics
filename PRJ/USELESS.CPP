void AddChimneyToHouse (int housestruct)
{
   SPH_openStructure (housestruct);
   SPH_setPickIdentifier (231);
   SPH_executeStructure (CHIMNEY_STRUCT);
   SPH_closeStructure ();
}

void TakeChimneyFromHouse (int housestruct)
{
   SPH_openStructure (housestruct);
   SPH_deleteElement ();
   SPH_deleteElement ();
   SPH_closeStructure ();
}
void CreateChimneyStructure ()
{
   matrix mat;

   point chim_verts[] = {
      {0.0, 0.0, 0.0},
      {4, 3, 0.0},
      {4, 7, 0.0},
      {0.0, 7, 0.0},
      {0.0, 0.0, -10},
      {4, 3, -10},
      {4, 7, -10},
      {0, 7, -10}
   };
   
   vertex_index chim_facets[] = 
      {0,1,2,3,  -1,
       4,7,6,5,  -1,
       7,4,0,3,  -1,
       1,5,6,2,  -1,
       7,3,2,6,  -1};

   SPH_openStructure (CHIMNEY_STRUCT);
   SPH_setInteriorColor (firebrick);
   SPH_translate (0.0,10.1, -30.0, mat);
   SPH_setModelingTransformation (mat, ASSIGN);
   SPH_polyhedron (8, 5, chim_verts, chim_facets);
   SPH_closeStructure();
}
void BuildEverything()
{
   register i;
   matrix temp;
   vector zerovec={0.0,0.0,0.0};

   CreateNormalizedHouseStructure();
   CreateAxesStructure();
   CreateTextStructure();
   SPH_openStructure (STREET_STRUCT);
   SPH_setInteriorColor (2);
   SPH_translate (0.0,0.0,0.0, temp);
   SPH_executeStructure (HOUSE_STRUCT);
   SPH_setInteriorColor (4);
   for (i=0; i<5; i++) {
      SPH_setInteriorColor (3+i);
      SPH_translate (20.0,0.0,0.0, temp);
      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure (HOUSE_STRUCT);
   }
   SPH_closeStructure();


   SPH_openStructure (NEIGHBORHOOD_STRUCT);
   SPH_executeStructure (STREET_STRUCT);
   for (i=0; i<2; i++) {
      SPH_translate(0.0,0.0,-70.0, temp);
      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure (STREET_STRUCT);
   }
   SPH_closeStructure();


   SPH_openStructure (FAKE_NEIGHBORHOOD_SIDE_STRUCT);
   SPH_setLineColor (7);
   SPH_executeStructure (FAKE_HOUSE_SIDE_STRUCT);
   for (i=0; i<2; i++) {
      SPH_translate(0.0,0.0,-70.0, temp);
      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure (FAKE_HOUSE_SIDE_STRUCT);
   }
   SPH_closeStructure();
/*CCCC1
   SPH_postRoot (FAKE_NEIGHBORHOOD_SIDE_STRUCT, SIDE_ORTHO_VIEW);
*/
   
   
   SPH_openStructure (FAKE_NEIGHBORHOOD_TOP_STRUCT);
   for (i=0; i<6; i++) {
      int j;
      SPH_setLineColor (i+2);
      for (j=0; j<3; j++) {
         SPH_translate (i*20.0, 0.0,-70.0*j, temp);
         SPH_setModelingTransformation (temp, ASSIGN);
         SPH_executeStructure (FAKE_HOUSE_TOP_STRUCT);
      }
   }
   SPH_closeStructure();
/*CCCCC
   SPH_postRoot (FAKE_NEIGHBORHOOD_TOP_STRUCT, TOP_ORTHO_VIEW);
*/
   SPH_openStructure (GRID_STRUCT);
   {
      register i;
      point p[2];

      SPH_setLineColor (yellow);

      /* DRAW THE LINES GOING FROM z=10 TO z=(-infinity) */
      MAT3_COPY_VEC (p[0], zerovec);
      MAT3_COPY_VEC (p[1], zerovec);
      p[0][Z] = (double)10;
      p[1][Z] = (double)-200;
      for (i=0; i<=200; i+=20) {
	 p[0][X] = p[1][X] = (double)i;
	 SPH_polyLine (2, p);
      }

      /* DRAW THE LINES GOING FROM x=-10 TO x=infinity */
      MAT3_COPY_VEC (p[0], zerovec);
      MAT3_COPY_VEC (p[1], zerovec);
      p[0][X] = (double)-10;
      p[1][X] = (double)200;
      for (i=0; i<=200; i+=20) {
	 p[0][Z] = p[1][Z] = (double)(-i);
	 SPH_polyLine (2, p);
      }
   }

   SPH_executeStructure (AXES_STRUCT);

   SPH_closeStructure ();

   SPH_postRoot (CAMERA_STRUCT, TOP_ORTHO_VIEW);
   SPH_postRoot (CAMERA_STRUCT, SIDE_ORTHO_VIEW);
   SPH_openStructure (14);
   SPH_closeStructure();
   InitVariables();
//   testa();
  BuildFinger ();
  BuildArm ();
  BuildRobot ();
  BuildBody();
}
/**     case 'g':
       sscanf (buffer, "g%d", &motion_granularity);
       DisplayMotionGranularity();
       break;
**/