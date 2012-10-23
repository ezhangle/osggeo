#ifndef osggeoviewer_h
#define osggeoviewer_h

/*
osgGeo - A collection of geoscientific extensions to OpenSceneGraph.
Copyright 2011 dGB Beheer B.V. and others.

http://osggeo.googlecode.com

osgGeo is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>

$Id: PolyLines.cpp 108 2012-10-08 08:32:40Z kristofer.tingdahl@dgbes.com $

*/

#ifdef USEQT
# include <QtGui/QApplication>
# include <osgQt/GraphicsWindowQt>
#endif

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

namespace osgGeo
{

class Viewer
{
public:
    			Viewer( int argc, char** argv );
    void		setSceneData( osg::Node* node );

    int			run();

#ifdef USEQT
    int			width() const { return widget_->width(); }
    int			height() const { return widget_->height(); }
#else
#endif

protected:
#ifdef USEQT
    QApplication 			app_;
    QWidget*				widget_;
#endif
    osg::ref_ptr<osgViewer::Viewer>	viewer_;
};


#ifdef USEQT
inline
Viewer::Viewer( int argc, char** argv )
    : app_( argc, argv )
    , widget_( 0 )
    , viewer_( 0 )
{

    viewer_ = new osgViewer::Viewer;
    viewer_->setCameraManipulator( new osgGA::TrackballManipulator );

    osgQt::initQtWindowingSystem();
    osgQt::setViewer( viewer_.get() );
    
    osgQt::GLWidget* glw = new osgQt::GLWidget;
    widget_ = glw;
    osgQt::GraphicsWindowQt* graphicswin = new osgQt::GraphicsWindowQt( glw );
    
    viewer_->getCamera()->setViewport( new osg::Viewport(0, 0, glw->width(), glw->height() ) );
    viewer_->getCamera()->setGraphicsContext( graphicswin );
}


inline
int Viewer::run()
{
    widget_->show();
    return app_.exec();
}
#else
#endif

inline
void Viewer::setSceneData( osg::Node* n )
{
    viewer_->setSceneData( n );
}


} //namespace

#endif
