#!/usr/bin/python

import JUCE

class HelloWorldComponent(JUCE.Component):
    def __init__(self):
        JUCE.Component.__init__(self)
        self.setSize(400, 200)
     
    def paint(self, g):
        print "paint!" 
        g.fillAll(JUCE.Colour(200, 1, 2))
        g.setFont (JUCE.Font(16.0));
        g.setColour (JUCE.Colour(0, 0, 0))
        g.drawText (JUCE.String("Hello World"), 10, 10, 30, 30, JUCE.Justify.centred, False) 

class HelloWorldWindow(JUCE.DocumentWindow):
    def __init__(self):
        JUCE.DocumentWindow.__init__(self)
        self.setVisible(True)        
        #self.centreWithSize(400, 200)

    def closeButtonPressed(self):
        print "closeButtonPressed:: CALLED !!"         
        JUCE.quit()           

def main():
    # These run after the JUCEApplication has started and creates a component
    # The component should be deleted in shutdown() as its called before JUCEApplication
    # terminates. Otherwise JUCEApplication terminates with windows open and leaks/errors
    mainWindow = None
    
    def __init():        
        global mainWindow 
        global comp       
        comp = HelloWorldComponent()
        #mainWindow = JUCE.DocumentWindow(JUCE.String("My Document Window"), JUCE.Colour(100, 100, 0), 7);
        mainWindow = HelloWorldWindow();
        mainWindow.setContentNonOwned(comp, True);
             
    def __shutdown():
        global mainWindow        
        global comp 
        del mainWindow
        del comp
        
    JUCE.mainLoop(__init, __shutdown)

if __name__ == '__main__':
    main()
