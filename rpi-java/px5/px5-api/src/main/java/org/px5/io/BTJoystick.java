package org.px5.io;

public class BTJoystick {
	public native void jsInput(String callbackName, String callbackSignature);
	public void refresh(int [] maps);
}
