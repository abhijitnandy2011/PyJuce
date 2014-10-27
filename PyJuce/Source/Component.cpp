#define BOOST_PYTHON_STATIC_LIB      
#include <boost/python.hpp>

using namespace boost::python;

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdexcept>





// ------------------------ JUCE Classes are exposed below this ------------------------------------

// Wrapper for Graphics as its non-copyable
struct GraphicsWrap {
    GraphicsWrap(){};
    Graphics *m_graphics;

    void fillAll(Colour colourToUse) { m_graphics->fillAll(colourToUse); }
    void setFont(const Font& newFont){ m_graphics->setFont(newFont); }
    void setColour(Colour newColour) { m_graphics->setColour(newColour); }

    void drawText(const String& text,
        int justification,
        int x, int y, int width, int height,
        bool useEllipsesIfTooBig) const 
    {
        m_graphics->drawText(text, 
            x, y, width, height,
            Justification(justification),
            useEllipsesIfTooBig);
    }


};
 
// Wrapper for component to support overrides in Python
struct PyJuceComponent :
    Component, 
    wrapper<Component>
{
    PyJuceComponent() // 2
    {}

    // hello constructor storing initial self parameter
    PyJuceComponent(const std::string& x) // 2
        : Component(x) {}

    // Override greet to call back into Python
    void userTriedToCloseWindow() // 4
    {
        this->get_override("userTriedToCloseWindow")();
    }

    // Override greet to call back into Python
    virtual void paint(Graphics& g) // 4
    {
        GraphicsWrap graphicsWrap;
        graphicsWrap.m_graphics = &g;
        this->get_override("paint")(graphicsWrap);
    }
};


// Overload test
//void (Graphics::*Graphics_fillAll_void)(Colour) const = &Graphics::fillAll;
//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Graphics_fillAll_void, Graphics::fillAll, 0, 0);

void exportComponent()
{
        class_<PyJuceComponent, boost::noncopyable>("Component")
            .def(init<std::string>())
            .def("paint", pure_virtual(&PyJuceComponent::paint))
            .def("setName", &PyJuceComponent::setName)
            .def("getName", &PyJuceComponent::getName, return_value_policy<return_by_value>())
            .def("getComponentID", &PyJuceComponent::getComponentID, return_value_policy<return_by_value>())
            .def("setOpaque", &PyJuceComponent::setOpaque)
            .def("setVisible", &PyJuceComponent::setVisible)
            .def("setSize", &PyJuceComponent::setSize)
            .def("addToDesktop", &PyJuceComponent::addToDesktop)
            .def("centreWithSize", &PyJuceComponent::centreWithSize)
            .def("userTriedToCloseWindow", &PyJuceComponent::userTriedToCloseWindow)            
            ;

        // Window enums
        enum_<ComponentPeer::StyleFlags>("StyleFlags")
            .value("windowAppearsOnTaskbar", ComponentPeer::windowAppearsOnTaskbar)
            .value("windowHasTitleBar", ComponentPeer::windowHasTitleBar)
            .value("windowIsResizable", ComponentPeer::windowIsResizable)
            .value("windowHasMinimiseButton", ComponentPeer::windowHasMinimiseButton)
            .value("windowHasMaximiseButton", ComponentPeer::windowHasMaximiseButton)
            .value("windowHasCloseButton", ComponentPeer::windowHasCloseButton)
            .value("windowHasDropShadow", ComponentPeer::windowHasDropShadow)
            ;

        // Colour enum
        class_<Colour>("Colour")
            .def(init<uint32>())
            .def(init<uint8, uint8, uint8>())
            ;

        class_<Image>("Image")
            ;

        class_<Font>("Font", init<float>())
            ;

        class_<GraphicsWrap>("Graphics")
            .def("fillAll", &GraphicsWrap::fillAll)
            .def("setFont", &GraphicsWrap::setFont)
            .def("setColour", &GraphicsWrap::setColour)
            .def("drawText", &GraphicsWrap::drawText)
            ;

        // This class is not required to be exposed yet
        /* class_<Justification>("Justification", init<int>())
            ;*/

        enum_<Justification::Flags>("Justify")
            .value("centred", Justification::centred)
            ;


       

}
