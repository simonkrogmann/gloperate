#include <gloperate-osg/OsgSceneStage.h>
#include <osg/Node>
#include <osgViewer/Viewer>
#include <gloperate/capabilities/ViewportCapability.h>
#include <gloperate/capabilities/InputCapability.h>
#include <gloperate-osg/OsgMouseHandler.h>
#include <gloperate-osg/OsgKeyboardHandler.h>


using namespace gloperate;
namespace gloperate_osg
{


void OsgSceneStage::osg_setScene(osg::Node * scene)
{
    // Release old scene
    if (m_scene) {
        m_scene->unref();
    }

    // Set new scene
    m_scene = scene;
    m_scene->ref();
    if (m_viewer) {
        m_viewer->setSceneData(m_scene);
    }
}

void OsgSceneStage::osg_initialize()
{
    // Release old data
    if (m_viewer) {
        m_viewer->unref();
    }
    if (m_embedded) {
        m_embedded->unref();
    }

    // Create OSG viewer
    m_viewer = new osgViewer::Viewer;
    m_viewer->ref();

    // Setup viewer using the already created window and OpenGL context
    m_embedded = m_viewer->setUpViewerAsEmbeddedInWindow(0, 0, 800, 600);
    m_embedded->ref();

    // Initialize camera
    m_viewer->getCamera()->setProjectionMatrixAsPerspective(45.0, 1.0, 0.5, 1000);
    m_viewer->getCamera()->setViewMatrix(osg::Matrix::lookAt(osg::Vec3(0, 0, 50), osg::Vec3(0, 0, 0), osg::Vec3(0, 1, 0))); 

    // Initialize viewer
    if (m_scene) {
        m_viewer->setSceneData(m_scene);
    }
    m_viewer->realize();
}

void OsgSceneStage::osg_process()
{
    // Check if painter has been initialized correctly
    if (m_viewer && m_embedded) {
        // Send resize-event
        // [TODO] How to pass this to the stage?
        /*
        m_embedded->resized(m_viewportCapability->x(), m_viewportCapability->y(), m_viewportCapability->width(), m_viewportCapability->height());
        */

        // Draw OSG scene
        m_viewer->frame();
    }
}

void OsgSceneStage::osg_cleanup()
{
    if (m_scene) {
        m_scene->unref();
    }

    if (m_embedded) {
        m_embedded->unref();
    }

    if (m_viewer) {
        m_viewer->unref();
    }
}


} // namespace gloperate_osg
