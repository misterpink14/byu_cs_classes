package Client.GUI.ImageSupport;

import javax.swing.JTabbedPane;

/**
 * ImageSupportView contains both the Field Help and Image Navigation tabs
 * 
 * @author Benjamin Thompson
 *
 */
@SuppressWarnings("serial")
public class ImageSupportView extends JTabbedPane
{
	public FieldHelpView help = new FieldHelpView();
	public ImageNavigationView imageNav = new ImageNavigationView();
	
	public ImageSupportView()
	{
		initUI();
	}
	
	private void initUI()
	{
		this.addTab("Field Help", help);
		help.setPreferredSize(this.getPreferredSize());
		this.addTab("Image Navigation", imageNav);
		imageNav.setPreferredSize(this.getPreferredSize());
	}
}
