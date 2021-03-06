/*
 * \copyright Copyright (c) 2014-2017 Governikus GmbH & Co. KG, Germany
 */

package com.governikus.ausweisapp2;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.nfc.NfcAdapter;
import android.nfc.tech.IsoDep;
import android.nfc.Tag;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;

import org.qtproject.qt5.android.bindings.QtActivity;


public class MainActivity extends QtActivity
{
	private static final String TAG = "AusweisApp2";

	private static Intent INITIAL_INTENT = null;

	private NfcForegroundDispatcher mNfcForegroundDispatcher;
	private class NfcForegroundDispatcher
	{
		private Activity mActivity;
		private NfcAdapter mAdapter;
		private PendingIntent mPendingIntent;
		private IntentFilter[] mFilters;
		private String[][] mTechLists;

		NfcForegroundDispatcher(Activity pActivity)
		{
			mActivity = pActivity;
			mAdapter = NfcAdapter.getDefaultAdapter(mActivity);
			mPendingIntent = PendingIntent.getActivity(
					mActivity, 0, new Intent(mActivity, mActivity.getClass()).addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP), 0);

			mFilters = new IntentFilter[] {
				new IntentFilter(NfcAdapter.ACTION_TECH_DISCOVERED)
			};
			mTechLists = new String[][] {
				new String[] {
					IsoDep.class.getName()
				}
			};
		}


		void enable()
		{
			if (mAdapter != null)
			{
				mAdapter.enableForegroundDispatch(mActivity, mPendingIntent, mFilters, mTechLists);
			}
		}


		void disable()
		{
			if (mAdapter != null)
			{
				mAdapter.disableForegroundDispatch(mActivity);
			}
		}


	}


	// required by IntentActivationHandler -> MainActivityAccessor
	public static String getInitialIntent()
	{
		if (INITIAL_INTENT != null)
		{
			return INITIAL_INTENT.getDataString();
		}
		else
		{
			Log.e(TAG, "No initial intent available, returning null");
			return null;
		}
	}


	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		Log.d(TAG, "onCreate (initial invocation of application): " + getIntent());
		super.onCreate(savedInstanceState);
		INITIAL_INTENT = getIntent();

		// register the broadcast receiver after loading the C++ library in super.onCreate()
		AndroidBluetoothReceiver.register(this);

		mNfcForegroundDispatcher = new NfcForegroundDispatcher(this);

		setRequestedOrientation(isTablet() ? ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE : ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
	}


	@Override
	protected void onNewIntent(Intent newIntent)
	{
		Log.d(TAG, "onNewIntent (subsequent invocation of application): " + newIntent);
		super.onNewIntent(newIntent);

		triggerActivation(newIntent.getDataString());
	}


	@Override
	public void onResume()
	{
		mNfcForegroundDispatcher.enable();
		super.onResume();
	}


	@Override
	public void onPause()
	{
		mNfcForegroundDispatcher.disable();
		super.onPause();
	}


	@Override
	protected void onDestroy()
	{
		Log.d(TAG, "onDestroy");

		// unregister the broadcast receiver before unloading the C++ library in super.onDestroy()
		AndroidBluetoothReceiver.unregister(this);

		super.onDestroy();
	}


	public void keepScreenOn(boolean pActivate)
	{
		Log.d(TAG, "Keep screen on: " + pActivate);
		if (pActivate)
		{
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		}
		else
		{
			getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		}
	}


	// required by UIPlugInQml::getPlatformSelectors()
	public boolean isTablet()
	{
		final Context context = getBaseContext();
		final int screenLayout = context.getResources().getConfiguration().screenLayout;
		final boolean xlarge = ((screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) == Configuration.SCREENLAYOUT_SIZE_XLARGE);
		final boolean large = ((screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) == Configuration.SCREENLAYOUT_SIZE_LARGE);

		return xlarge || large;
	}


	private native void triggerActivation(String lastIntent);
}
