package com.lettersearch.core;

public class JniSearchCore {
	public static final String TAG = JniSearchCore.class.getCanonicalName();
	static {
		System.loadLibrary("pinyinsearch");
	}

	public static native boolean searchPinYin(Object[] source, String input, int[] colors);

	public static native boolean searchMorePinYin(Object[] source, String input, int[] colors);

	private static int getCount(CharSequence text) {
		int count = 0;
		for (int i = 0; i < text.length(); i++) {
			if (text.charAt(i) == ' ') {
				count++;
			}
		}
		return count;
	}

	private static boolean search(String[] mtemp, Object[] source, String input, int[] colors, int index) {

		if (mtemp == null) {
			mtemp = new String[source.length];
		}

		int[][] mints = new int[source.length][];
		int size = 0;

		for (int i = 0; i < source.length; i++) {
			String str = mtemp[i] = source[i].toString();
			int count = 0;
			for (int j = 0; j < str.length(); j++) {
				if (mtemp[j].charAt(j) == ' ') {
					count++;
				}
			}

			if (count > 1) {
				mints[i] = new int[] { i, 1 };
				size++;
				mtemp[i] = str.substring(0, str.indexOf(' '));
			}
		}

		for (int i = 0; i < size; i++) {
			int[] result = mints[i];
		}
		return false;
	}

}
