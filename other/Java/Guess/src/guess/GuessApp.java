/*
 * GuessApp.java
 */

package guess;

import org.jdesktop.application.Application;
import org.jdesktop.application.SingleFrameApplication;

/**
 * The main class of the application.
 */
public class GuessApp extends SingleFrameApplication {


    @Override protected void startup() {
        show(new GuessView(this));
    }

    @Override protected void configureWindow(java.awt.Window root) {
        this.getMainFrame().setResizable(false);
    }

    public static GuessApp getApplication() {
        return Application.getInstance(GuessApp.class);
    }

    public static void main(String[] args) {
        launch(GuessApp.class, args);
    }
}
