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
	    sText += "2.2.4<br />\n";
	    sText += "© 2012-2013 Leon Anavi<br />\n";
	    sText += "<font color=\"#006BC2\"><a href=\"http://anavi.org/\">http://anavi.org/</a></font><br />\n<br />\n";
    
	    sText += getString(R.string.about_info1, "<font color=\"#006BC2\"><a href=\"https://gitorious.org/location2sms\">", "</a></font>");
	    
	    sText += getString(R.string.about_info2);
	    sText += "<br />\n<br />\n";
	    sText += String.format("<b>%s</b>", getString(R.string.about_privacy_policy_title));
	    sText += "<br />\n";
	    sText += getString(R.string.about_privacy_policy_text);
	    return sText;
	}
	//------------------------------------------------------------------------------

}
