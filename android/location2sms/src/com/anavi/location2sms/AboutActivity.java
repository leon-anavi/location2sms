package com.anavi.location2sms;

import android.app.Activity;
import android.os.Bundle;
import android.text.Html;
import android.text.method.LinkMovementMethod;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

public class AboutActivity extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    
        //remove title and expand to full screen
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(
        		WindowManager.LayoutParams.FLAG_FULLSCREEN, 
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
	
	    setContentView(R.layout.about);

 		TextView labelInfo = (TextView) findViewById(R.id.about_labelInfo);
 		labelInfo.setMovementMethod(LinkMovementMethod.getInstance());
 		labelInfo.setText(Html.fromHtml(getInfoText()), TextView.BufferType.SPANNABLE);
	    
	}
	
	private String getInfoText()
	{
	    String sText = "<h2><i>location<font color=\"#006BC2\">2</font>sms</i></h2>\n";
	    sText += "2.2.1<br />\n";
	    sText += "© 2012 Leon Anavi<br />\n";
	    sText += "http://anavi.org/<br />\n<br />\n";
    
	    String sLic = "This is an open source application available under GPLv3 licence at %sGitorious: https://gitorious.org/location2sms%s. ";
	    sText += String.format(sLic, "<font color=\"#006BC2\"><a href=\"https://gitorious.org/location2sms\">", "</a></font>");
	    
	    sText += "The application depends on GPS quality that the device delivers. ";
	    sText += "It is powered by Google Maps API and requires Internet connection. ";
	    sText += "Position accuracy of about 20 meters can be expected. ";
	    sText += "<br />\n<br />\n";
	    sText += "<b>Privacy Policy</b>";
	    sText += "<br />\n";
	    sText += "The Application does not collect or transmits personally ";
	    sText += "identifiable information and does not monitor your ";
	    sText += "personal use of the Application.";
	    return sText;
	}
	//------------------------------------------------------------------------------

}
