package program;

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class CreatePostSystemlDialog extends JDialog  implements  ActionListener {
	private static final long serialVersionUID = 1L;
	private JPanel p1,p2;
    private JButton ok, cancel;
    private JLabel lbl_br, lbl_tr, lbl_pk;
    private JSlider sl_br, sl_tr, sl_pk;
    private PostSystemPanel rs;
 
    public CreatePostSystemlDialog(Main parent, PostSystemPanel pan, String title) {
    	super((Main)parent,title,true);
    	rs = pan;

    	setSize(600,400);
	
		setBackground(new Color(100,230,255));
		p1 = new JPanel();
		p2 = new JPanel();
	
		p1.setLayout(new GridLayout(6,1,10,5));
		lbl_br = new JLabel("Number of branches",JLabel.CENTER);
		p1.add(lbl_br);
		lbl_tr = new JLabel("Number of trucks per branch",JLabel.CENTER);
//		lbl_pk = new JLabel("Number of packages",JLabel.CENTER);
		
		sl_br = new JSlider(1,10);
		sl_br.setMajorTickSpacing(1);
		sl_br.setMinorTickSpacing(1);
		sl_br.setPaintTicks(true);
		sl_br.setPaintLabels(true);
		p1.add(sl_br);
		
		p1.add(lbl_tr);
		sl_tr = new JSlider(1,10);
		sl_tr.setMajorTickSpacing(1);
		sl_tr.setMinorTickSpacing(1);
		sl_tr.setPaintTicks(true);
		sl_tr.setPaintLabels(true);
		p1.add(sl_tr);
	
//		p1.add(lbl_pk);
//		sl_pk = new JSlider(2,20);
//		sl_pk.setMajorTickSpacing(2);
//		sl_pk.setMinorTickSpacing(1);
//		sl_pk.setPaintTicks(true);
//		sl_pk.setPaintLabels(true);
//		p1.add(sl_pk);
		
		p2.setLayout(new GridLayout(1,2,5,5));
		ok=new JButton("OK");
		ok.addActionListener(this);
		ok.setBackground(Color.lightGray);
		p2.add(ok);		
		cancel=new JButton("Cancel");
		cancel.addActionListener(this);
		cancel.setBackground(Color.lightGray);
		p2.add(cancel);
		
		setLayout(new BorderLayout());
		add("North" , p1);
		add("South" , p2);
    }
    
    

    public void actionPerformed(ActionEvent e) {
 		if(e.getSource() == ok){
		    rs.createNewPostSystem(sl_br.getValue(),sl_tr.getValue());
		    setVisible(false);
		}
		else 
		    setVisible(false);
    }
}
