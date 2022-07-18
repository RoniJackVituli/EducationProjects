package program;

import java.awt.*;
import java.util.List;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.imageio.ImageIO;
import javax.swing.*;

import components.*;
import components.Package;

import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.CyclicBarrier;

public class PostSystemPanel extends JPanel implements ActionListener {
	private static final long serialVersionUID = 1L;
	private Main frame;
	private JPanel p1;
	private JButton[] b_num;
	private String[] names = {"Create system","Start","Stop","Resume","All packages info","Branch info","CloneBranch","Restore", "Report"};
	private JScrollPane scrollPane;
	private boolean isTableVisible = false;
	private boolean isTable2Visible = false;
	private int colorInd = 0;
	private boolean started = false;
	private MainOffice game = null;
	private static int packagesNumber;
	private static int branchesNumber;
	private static int trucksNumber;
	private TextAreaAsLabel w;

	public static void addBranches() {
		branchesNumber++;
	}

	public static void subBranches() {
		branchesNumber--;
	}
	public PostSystemPanel(Main f) {
		frame = f;
		isTableVisible = false;
		setBackground(new Color(255,255,255));
		p1=new JPanel();
		p1.setLayout(new GridLayout(1,7,0,0));
		p1.setBackground(new Color(0,150,255));
		b_num=new JButton[names.length];

		for(int i=0;i<names.length;i++) {
			b_num[i]=new JButton(names[i]);
			b_num[i].addActionListener(this);
			b_num[i].setBackground(Color.lightGray);
			p1.add(b_num[i]);		
		}

		setLayout(new BorderLayout());
		add("South", p1);
	}	


	public void createNewPostSystem(int branches, int trucks) {
		if (started) 
			return;

		System.out.println("I CREATED!");
		game = MainOffice.getInstance(branches, trucks, this);
		game.addObserver();
		// game = new MainOffice(branches, trucks, this, packages);
		packagesNumber = 20;
		trucksNumber = trucks;
		branchesNumber = branches;
		repaint();
	}


	public void paintComponent(Graphics g) {
		super.paintComponent(g);	

		if (game==null) return;
		int offset, offset2;

		Hub hub = game.getHub();
		ArrayList<Branch> branches = hub.getBranches();
		if(branchesNumber - 1 != 0) {
			offset = 403/(branchesNumber-1);
			offset2 = 140/(branchesNumber-1);
		}else {
			offset2 = 140;
			offset = 403;
		}
		int y=100;
		int y2=246; 	
		g.setColor(new Color(0,102,0));
		g.fillRect(1120, 216, 40, 200);


		for (Branch br: branches) {
			br.paintComponent(g,y,y2);
			y+=offset;
			y2+=offset2;
		}


		int x = 150;
		int offset3 = (1154-300)/(packagesNumber-1);

		for (Package p: game.getPack()) {
			p.paintComponent(g,x,offset);
			x+=offset3;
		}


		for (Branch br: branches) {
			for(Truck tr: br.getTrucks()) {
				tr.paintComponent(g);
			}
		}

		for(Truck tr: hub.getTrucks()) {
			tr.paintComponent(g);
		}

	}



	public void setColorIndex(int ind) {
		this.colorInd = ind;
		repaint();
	}


	public void setBackgr(int num) {
		switch(num) {
		case 0:
			setBackground(new Color(255,255,255));
			break;
		case 1:
			setBackground(new Color(0,150,255));
			break;

		}
		repaint();
	}



	public void add(){
		CreatePostSystemlDialog dial = new CreatePostSystemlDialog(frame,this,"Create post system");
		dial.setVisible(true);
	}



	public void start() {
		if (game==null || started) 
			return;
		Thread t = new Thread(game);
		started = true;
		System.out.println("I START!!!!!!!!!");
		t.start();
	}

	public void resume() {
		if (game == null) return;
		game.setResume();
	}

	public void stop() {
		if (game == null) return;
		game.setSuspend();
	}


	public void info() {
		if (game == null || !started) return;
		if(isTable2Visible == true) {
			scrollPane.setVisible(false);
			isTable2Visible = false;
		}
		if(isTableVisible == false) {
			int i=0;
			String[] columnNames = {"Package ID", "Sender", "Destination", "Priority", "Staus"};
			ArrayList<Package> packages = game.getPack();
			String [][] data = new String[packages.size()][columnNames.length];
			for(Package p : packages) {
				data[i][0] = ""+p.getPackageID();
				data[i][1] = ""+p.getSenderAddress();
				data[i][2] = ""+p.getDestinationAddress();
				data[i][3] = ""+p.getPriority();
				data[i][4] = ""+p.getStatus();
				i++;
			}
			JTable table = new JTable(data, columnNames);
			scrollPane = new JScrollPane(table);
			scrollPane.setSize(450,table.getRowHeight()*(packages.size())+24);
			add( scrollPane, BorderLayout.CENTER );
			isTableVisible = true;
		}
		else
			isTableVisible = false;

		scrollPane.setVisible(isTableVisible);
		repaint();
	}


	public void branchInfo() {
		if (game == null || !started) return;

		if(scrollPane!=null) scrollPane.setVisible(false);
		isTableVisible = false;
		isTable2Visible = false;
		String[] branchesStrs = new String[game.getHub().getBranches().size()+1];
		branchesStrs[0] = "Sorting center";
		for(int i=1; i<branchesStrs.length; i++)
			branchesStrs[i] = "Branch "+i;
		JComboBox cb = new JComboBox(branchesStrs);
		String[] options = { "OK", "Cancel" };
		String title = "Choose branch";
		int selection = JOptionPane.showOptionDialog(null, cb, title,
				JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options,
				options[0]);
		if (selection==1) return;
		//System.out.println(cb.getSelectedIndex());
		if(isTable2Visible == false) {
			int i=0;
			String[] columnNames = {"Package ID", "Sender", "Destination", "Priority", "Staus"};
			Branch branch;
			List<Package> packages = null;
			int size=0;
			if(cb.getSelectedIndex()==0) {
				packages = game.getHub().getPackages();
				size = packages.size();
			}
			else {
				packages = game.getHub().getBranches().get(cb.getSelectedIndex()-1).getPackages();
				size = packages.size();
				int diff = 0;
				for(Package p : packages) {
					if (p.getStatus()==Status.BRANCH_STORAGE) {
						diff++;
					}
				}
				size = size - diff/2;
			}
			String [][] data = new String[size][columnNames.length];
			for(Package p : packages) {
				boolean flag = false;
				for(int j=0; j<i; j++)
					if (data[j][0].equals(""+p.getPackageID())) {
						flag = true;
						break;
					}
				if (flag) continue;
				data[i][0] = ""+p.getPackageID();
				data[i][1] = ""+p.getSenderAddress();
				data[i][2] = ""+p.getDestinationAddress();
				data[i][3] = ""+p.getPriority();
				data[i][4] = ""+p.getStatus();
				i++;
			}
			JTable table = new JTable(data, columnNames);
			scrollPane = new JScrollPane(table);
			scrollPane.setSize(450,table.getRowHeight()*(size)+24);
			add( scrollPane, BorderLayout.CENTER );
			isTable2Visible = true;
		}
		else
			isTable2Visible = false;

		scrollPane.setVisible(isTable2Visible);
		repaint();
	}

	public void cloneBranch() {
		if (game == null || !started) return;
		if(scrollPane!=null) scrollPane.setVisible(false);
		isTableVisible = false;
		isTable2Visible = false;
		String[] branchesStrs = new String[game.getHub().getBranches().size()];
		for(int i=0; i<branchesStrs.length; i++)
			branchesStrs[i] = "Branch "+ (i+1);
		JComboBox cb = new JComboBox(branchesStrs);
		String[] options = { "OK", "Cancel" };
		String title = "Choose branch";
		int selection = JOptionPane.showOptionDialog(null, cb, title,
				JOptionPane.DEFAULT_OPTION, JOptionPane.PLAIN_MESSAGE, null, options,
				options[0]);
		String Sindex = (String)cb.getSelectedItem();
		int index = bringTheNum(Sindex);
		if(selection == 1) return;
		System.out.println("INDEX IS ===> " + index);
		game.addBranch(index);

	}
	
	public int bringTheNum(String s) {
		char [] chars = s.toCharArray();
		for(char c : chars)
			if(Character.isDigit(c))
				return Character.getNumericValue(c);
		return 0;
	}

	public void Restore() {
		if (game == null || !started) return;
		game.restore();
	}

	public void Report() {
		if (game == null || !started) return;
		w = new TextAreaAsLabel();
		w.TEXT();
	}

	public void destroy(){  	        
		System.exit(0);
	}


	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == b_num[0]) 
			add();
		else if(e.getSource() == b_num[1]) 
			start();
		else if(e.getSource() == b_num[2])  
			stop();
		else if(e.getSource() == b_num[3])  
			resume(); 
		else if(e.getSource() == b_num[4])  
			info();
		else if(e.getSource() == b_num[5])  
			branchInfo();
		else if(e.getSource() == b_num[6])
			cloneBranch();
		else if(e.getSource() == b_num[7])
			Restore();
		else if(e.getSource() == b_num[8])
			Report();
	}


}