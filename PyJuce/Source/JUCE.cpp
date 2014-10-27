//#include "stdafx.h"
#include "JUCE.h"
#include <stdexcept>


// ----------------- JUCE Application startup/bootstrap code ------------------------

PyObject* PyJuceApplication::sInitializeHook = nullptr;
PyObject* PyJuceApplication::sShutdownHook = nullptr;

static juce::JUCEApplicationBase* juce_CreateApplication() {
    return new PyJuceApplication();
}

void mainLoop(PyObject *initialize, PyObject *shutdown)
{
    //juce::JUCEApplication::main(0, new PyJUCEApplication(applicationName, initialiseCallback, shutdownCallback));
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication;
    char argv[1][10] = { "JUCE" };

    PyJuceApplication::sInitializeHook = initialize;
    PyJuceApplication::sShutdownHook   = shutdown;

    juce::JUCEApplicationBase::main();
}

void quit()
{
    juce::JUCEApplication::quit();
}

// Juce module export functions
//void export_juce_gui_basics();
void exportComponent();
void exportDocumentWindow();


// ------------------------ JUCE Classes are exposed below this ------------------------------------

// Binding starts off from here...
BOOST_PYTHON_MODULE(JUCE)
{
    class_<String>("String", init<char*>())
        .def("toStdString", &String::toStdString);

   // export_juce_gui_basics();

    exportComponent();
    exportDocumentWindow();

    def("mainLoop", &mainLoop);
    def("quit", &quit);
}
