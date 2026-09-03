#pragma once

#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TTimeStamp.h"
#include "TOF_TreeDataStg1.h"
#include "TOF_TreeDataStg2.h"
#include "TOF_Constants.h"
#include "TOF_TdcQdcCalibration.h"
#include <iostream>

#ifndef _TOF_CONVERTSTG1TOSTG2_H
#define _TOF_CONVERTSTG1TOSTG2_H

class TOF_ConvertStg1toStg2 : public TObject
{
	public: 
	  //TOF_ConvertStg1toStg2() = default;
	  TOF_ConvertStg1toStg2() {
			setClassStg1();
			setClassStg2();
			return;
		}
    
		inline static TOF_ConvertStg1toStg2 * theConvStg{nullptr}; 
		static TOF_ConvertStg1toStg2 *getInstance() {
			if( theConvStg == nullptr ) {
				theConvStg = new TOF_ConvertStg1toStg2;
			}
			return theConvStg;
		}

    ~TOF_ConvertStg1toStg2() override {
			if (fStg1) delete fStg1;
			if (fStg2) delete fStg2;
		}

	private:
		TOF_TreeDataStg1*      fStg1 {nullptr}; // input
		TOF_TreeDataStg2*      fStg2 {nullptr}; // output
    TOF_TdcQdcCalibration* fCalib{nullptr};
		void setClassStg1();
		void setClassStg2();

	public: 
		int  setInputPathStg1( const char* fpath );
		int  addBranches_TSandConnID();
		//int  addConnIdBranches();

    int  loadCalibration( const char* fTdcCalib, const char* fQdcCalib ) {
			fCalib = TOF_TdcQdcCalibration::getInstance();
			return fCalib->readCalibrationFiles( fTdcCalib, fQdcCalib );
		}
		int  loadCalibration( const char* dirPath ) {
			fCalib = TOF_TdcQdcCalibration::getInstance();
			return fCalib->readCalibrationFiles( dirPath );
		}

    void convertStg1ToStg2( const char* kPathStg1, const char* kPathStg2="", const char* calibDir="" );
		TOF_TreeDataStg1* getStg1() {return fStg1; };
		TOF_TreeDataStg2* getStg2() {return fStg2; };

    ClassDefOverride(TOF_ConvertStg1toStg2, 2)	
};

#endif
