#define BOOST_PYTHON_STATIC_LIB      
#include <boost/python.hpp>

using namespace boost::python;

#include "../JuceLibraryCode/JuceHeader.h"
#include <stdexcept>





// ------------------------ JUCE Classes are exposed below this ------------------------------------



// Wrapper class
struct PyJuceDocumentWindow :
    DocumentWindow,
    wrapper<DocumentWindow>
{
    PyJuceDocumentWindow() // 2
        : DocumentWindow("Juce Application", Colour(100, 100, 100), DocumentWindow::allButtons)
    {}

    // hello constructor storing initial self parameter
    /* PyJuceDocumentWindow(const std::string& title)
    : DocumentWindow(x) {}*/

    // Override greet to call back into Python
    void closeButtonPressed() // 4
    {
        this->get_override("closeButtonPressed")();
    }
};


//---------------------------- Actual Export -------------------------------------------

void exportDocumentWindow()
{
    class_<PyJuceDocumentWindow, boost::noncopyable>("DocumentWindow")
        .def("setContentNonOwned", &DocumentWindow::setContentNonOwned)
        .def("centreWithSize", &DocumentWindow::centreWithSize)
        .def("setVisible", &DocumentWindow::setVisible)
        ;

}
