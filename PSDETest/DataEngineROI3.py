#!/usr/bin/env python
# -*- coding: utf-8 -*-

import Sofa
from ROI import BoxROI



class MyDataEngine3(Sofa.PythonScriptDataEngine):       
    
    def parse(self):        
        # this is the ideal place to define inputs and outputs!
        
        self.addNewInput('Positions',datatype='p',value='@tetras.rest_position')        
        self.addNewInput('Tetrahedra',datatype='t',value='@PSDE2.TetrahedraOutliers')        
        self.addNewOutput('TetrahedraInliers',datatype='t')                
        self.addNewOutput('TetrahedraOutliers',datatype='t')        

    def update(self):
	pass

    def init(self):                
        
        MyBoxROI = BoxROI(10, -30, 60, 30, 30, 100, self.Positions)    
        MyBoxROI.calcTetrasInROI(self.Tetrahedra)        
        self.TetrahedraInliers = MyBoxROI.Inliers        
        self.TetrahedraOutliers = MyBoxROI.Outliers
        



