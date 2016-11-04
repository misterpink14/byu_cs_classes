package Client.GUI;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import Client.Controller;


@SuppressWarnings("serial")
public class LoginView extends JFrame 
{
    JTextField user;
    JPasswordField pass;
    WelcomeView welcome;
    
	public LoginView()
	{
		initLogin();
	}
		
	private void initLogin()
	{ 
		JPanel basic = new JPanel();
        basic.setLayout(new BoxLayout(basic, BoxLayout.Y_AXIS));
        add(basic);

        basic.add(Box.createVerticalGlue());

        JPanel bottom1 = new JPanel();
        JPanel bottom2 = new JPanel();

        user = new JTextField(8);
        pass = new JPasswordField(8);
        JButton login = new JButton("Login");
        
        login.addActionListener(new ActionListener()
        {

			@Override
			public void actionPerformed(ActionEvent e)
			{
				System.out.println(new String(pass.getPassword()));
					Controller.validateUser(user.getText(), new String(pass.getPassword()));
					setAlwaysOnTop(false);
					new WelcomeView();
			}
        	
        });
        
        user.setText("sheila");
        pass.setText("parker");

        bottom1.add(new JLabel("Username: "));
        bottom1.add(user);
        bottom2.add(new JLabel("Password: "));
        bottom2.add(pass);

        basic.add(bottom1);
        basic.add(bottom2);
        basic.add(login);
        
        login = new JButton("Exit");
        login.addActionListener(new ActionListener()
        {

			@Override
			public void actionPerformed(ActionEvent e)
			{
				System.exit(0);
			}
        	
        });


        setAlwaysOnTop(true);
        setTitle("Login to Indexer");
        setSize(376, 118);
        setLocationRelativeTo(null);
        setResizable(false);
		setVisible(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
}
