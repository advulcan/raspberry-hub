package org.px5;

import org.px5.io.BTJoystick;

/**
 * Hello world!
 *
 */
public class App {
	static {
		System.loadLibrary("btjoystick");
	}
	public static void main(String[] args) {
		System.out.println("Hello World!");
		BTJoystick js = new BTJoystick();
		js.jsInput();
	}
}
