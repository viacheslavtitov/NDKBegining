package eleks.com.ndk.begin.app;

import android.app.Application;

public class MyApplication extends Application {

	static {
		System.loadLibrary("NDKBegin");
	}

}
