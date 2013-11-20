package eleks.com.ndk.begin.app;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {

	native String getStringFromFile(String path) throws IOException;

	native void writeByteArrayToFile(String path, byte[] b) throws IOException;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		callNdk();
	}

	private void callNdk() {
		try {
			writeByteArrayToFile("/mnt/sdcard/FFMPEG/my.txt",
					getByteArrayFromAssetsFile());
		} catch (IOException e) {
			e.printStackTrace();
		}
		TextView tv = (TextView) findViewById(R.id.tvText);
		try {
			tv.setText(getStringFromFile("/mnt/sdcard/FFMPEG/my.txt"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private byte[] getByteArrayFromAssetsFile() throws IOException {
		InputStream is = null;
		ByteArrayOutputStream buffer = null;
		byte[] data = null;
		try {
			is = getAssets().open("file.txt");
			buffer = new ByteArrayOutputStream();
			int nRead;
			data = new byte[1024];
			while ((nRead = is.read(data, 0, data.length)) != -1) {
				buffer.write(data, 0, nRead);
			}

			buffer.flush();
		} finally {
			if (buffer != null) {
				buffer.close();
			}
			if (is != null) {
				is.close();
			}
		}
		return data;
	}

}
