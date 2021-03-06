/****************************************************************************
*                                                                           *
*   IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.       *
*                                                                           *
*   By downloading, copying, installing or using the software you agree to  *
*   this license. If you do not agree to this license, do not download,     *
*   install, copy or use the software.                                      *
*                                                                           *
*                           License Agreement                               *
*                   For Vision Open Statistical Models                      *
*                                                                           *
*   Copyright (C):      2006~2012 by JIA Pei, all rights reserved.          *
*                                                                           *
*   VOSM is free software under the terms of the GNU Lesser General Public  *
*   License (GNU LGPL) as published by the Free Software Foundation; either *
*   version 3.0 of the License, or (at your option) any later version.      *
*   You can use it, modify it, redistribute it, etc; and redistribution and *
*   use in source and binary forms, with or without modification, are       *
*   permitted provided that the following conditions are met:               *
*                                                                           *
*   a) Redistribution's of source code must retain this whole paragraph of  *
*   copyright notice, including this list of conditions and all the         *
*   following contents in this  copyright paragraph.                        *
*                                                                           *
*   b) Redistribution's in binary form must reproduce this whole paragraph  *
*   of copyright notice, including this list of conditions and all the      *
*   following contents in this copyright paragraph, and/or other materials  *
*   provided with the distribution.                                         *
*                                                                           *
*   c) The name of the copyright holders may not be used to endorse or      *
*   promote products derived from this software without specific prior      *
*   written permission.                                                     *
*                                                                           *
*   Any publications based on this code must cite the following five papers,*
*   technical reports and on-line materials.                                *
*   1) P. JIA, 2D Statistical Models, Technical Report of Vision Open       *
*   Working Group, 2st Edition, October 21, 2010.                           *
*   http://www.visionopen.com/members/jiapei/publications/pei_sm2dreport2010.pdf*
*   2) P. JIA. Audio-visual based HMI for an Intelligent Wheelchair.        *
*   PhD thesis, University of Essex, February, 2011.                        *
*   http://www.visionopen.com/members/jiapei/publications/pei_phdthesis2010.pdf*
*   3) T. Cootes and C. Taylor. Statistical models of appearance for        *
*   computer vision. Technical report, Imaging Science and Biomedical       *
*   Engineering, University of Manchester, March 8, 2004.                   *
*   http://www.isbe.man.ac.uk/~bim/Models/app_models.pdf                    *
*   4) I. Matthews and S. Baker. Active appearance models revisited.        *
*   International Journal of Computer Vision, 60(2):135--164, November 2004.*
*   http://www.ri.cmu.edu/pub_files/pub4/matthews_iain_2004_2/matthews_iain_2004_2.pdf*
*   5) M. B. Stegmann, Active Appearance Models: Theory, Extensions and     *
*   Cases, 2000.                                                            *
*   http://www2.imm.dtu.dk/~aam/main/                                       *
*                                                                           *
* Version:          0.4                                                     *
* Author:           JIA Pei                                                 *
* Contact:          jp4work@gmail.com                                       *
* URL:              http://www.visionopen.com                               *
* Create Date:      2008-04-03                                              *
* Revise Date:      2012-03-22                                              *
*****************************************************************************/

#ifndef __VO_FACEPART_H__
#define __VO_FACEPART_H__

#include <vector>
#include <iostream>
#include <string>


using namespace std;


/** 
* @author       JIA Pei
* @brief        Ellipse - used to describe 2D Gaussian distribution.
*/
class VO_FacePart
{
friend ostream& operator<<(ostream& os, const VO_FacePart& facepart);
friend istream& operator>>(istream& is, VO_FacePart& facepart);
friend class VO_FaceParts;
private:
    /** type */
    unsigned int                        m_iType;

    /** open or closed */
    bool                                m_bClosed;

    /** index vector */
    vector<unsigned int>                m_vIndexes;

    void                                init()
    {
        this->m_iType = 0;      // actually, type 0 is just a default value, which is not used at all
        this->m_bClosed = false;
        this->m_vIndexes.clear();
    }

    void                                CopyData(const VO_FacePart &iFacePart)
    {
        this->m_iType       = iFacePart.GetType();
        this->m_bClosed     = iFacePart.IsClosedOrNot();
        this->m_vIndexes.resize( iFacePart.GetIndexes().size() );
        this->m_vIndexes        = iFacePart.GetIndexes();
    }

public:
    enum {
        WHOLEFACE = 0,
        CHIN = 1,
        LEFTEYEBROW = 2,
        RIGHTEYEBROW = 3,
        LEFTEYE = 4,
        RIGHTEYE = 5,
        NOSE = 6,
        NOSTRIL = 7,
        NOSETIP = 8,
        LIPOUTERLINE = 9,
        LIPINNERLINE = 10,
        LIPUPPEROUTERLINE = 11,
        LIPUPPERINNERLINE = 12,
        LIPDOWNEROUTERLINE = 13,
        LIPDOWNERINNERLINE = 14,
        LEFTSIDEPOINTS = 15,
        RIGHTSIDEPOINTS = 16,
        MIDLINEPOINTS = 17,
        EYECORNERPOINTS = 18,
        MOUTHCORNERPOINTS = 19,
        PITCHAXISLINEPOINTS = 20,
        LEFTIRIS = 21,
        RIGHTIRIS = 22,
        LEFTEAR = 23,
        RIGHTEAR = 24,
        WHOLEMOUTH = 25,
        NOSECENTRALAREA = 26};

    /** Default constructor to create a VO_FaceParts object */
    VO_FacePart()                       { this->init(); }

    /** Copy constructor */
    VO_FacePart( const VO_FacePart &iFacePart )
    {
                                        this->CopyData(iFacePart);
    }

    /** Destructor */
    virtual ~VO_FacePart()              { this->m_vIndexes.clear(); }

    /** operator= overloading, similar to copy constructor */
    VO_FacePart&  operator=(const VO_FacePart &iFacePart)
    {
                                        this->CopyData(iFacePart);
                                        return *this;
    }

    void                                clear() { this->init();}

    unsigned int                        GetType() const {return this->m_iType;}
    bool                                IsClosedOrNot() const {return this->m_bClosed;}
    vector<unsigned int>                GetIndexes() const {return this->m_vIndexes;}

    void                                SetType(unsigned int type) {this->m_iType = type;}
    void                                SetClosedOrNot(bool close) {this->m_bClosed = close;}
    void                                SetIndexes(vector<unsigned int> indexes) {this->m_vIndexes = indexes;}

};

#endif      // __VO_FACEPART_H__

