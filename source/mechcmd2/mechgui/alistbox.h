//===========================================================================//
// Copyright (C) Microsoft Corporation. All rights reserved.                 //
//===========================================================================//

#pragma once

#ifndef ALISTBOX_H
#define ALISTBOX_H

#include <gui/ascroll.h>
#include <gui/aedit.h>
#include <gui/afont.h>

#include "estring.h"

namespace mechgui {

#define MAX_LIST_ITEMS			128
#define	TOO_MANY_ITEMS			0xEEEE0001
#define ITEM_OUT_OF_RANGE		0xEEEE0002


	class aListItem : public aObject
	{
	public:

		enum State
		{
			ENABLED = 0,
			SELECTED,
			HIGHLITE,
			PRESSED_HIGHLITE,
			DISABLED,

		};

		virtual void update(){ aObject::update(); }
		virtual void render(){ aObject::render(); }

		void setState( int newState ){ state = (State)newState; }
		State getState( ) { return state; }

		void select(){ state = SELECTED; }
		void disable(){ state = DISABLED; }
		void highlite(){ state = HIGHLITE; }
		void deselect(){ state = state == DISABLED ? DISABLED : ENABLED; }

		virtual bool isChecked() { return false; }
		virtual void setCheck( bool ){}



	protected:

		State		state;
	};

	class aTextListItem  : public aListItem
	{
	public:

		aTextListItem(HGOSFONT3D newFont); // need the font, so we can determine the size
		aTextListItem( const aFont& newFont );
		aTextListItem( int32_t fontResID );

		virtual ~aTextListItem();

		void		setText( PCSTR text );
		void		setText( int32_t resID );
		PCSTR getText() const;
		void		sizeToText();

		void init( FitIniFile& file, PCSTR blockName = "Text0" );

		virtual void render();
		void		setAlignment( int32_t newA ){ alignment = newA; }

		void		forceToTop( bool bForce ) { bForceToTop = bForce; }

	protected:
		aTextListItem() {}
		void init( int32_t fontResID );


		aFont		font;
		EString		text;
		int32_t		alignment;

		bool		bForceToTop;


	};

	class aAnimTextListItem : public aTextListItem
	{

	public:

		aAnimTextListItem(HGOSFONT3D newFont) : aTextListItem( newFont ) {}
		aAnimTextListItem( const aFont& newFont ) : aTextListItem( newFont ){}
		aAnimTextListItem( int32_t fontResID ) : aTextListItem( fontResID ){}

		aAnimTextListItem( const aAnimTextListItem& src ); 
		aAnimTextListItem& operator=( const aAnimTextListItem& src ); 

		void init( FitIniFile& file, PCSTR blockName = "Text0" );
		virtual void render();
		virtual void update();

	protected:

		aAnimGroup	animInfo;
		void CopyData( const aAnimTextListItem& src );

	};

	class aLocalizedListItem : public aAnimTextListItem
	{
	public:
		aLocalizedListItem();
		virtual int32_t	init( FitIniFile* file, PCSTR blockName );
		virtual void		render();

		void			setHiddenText( PCSTR pText ){ hiddenText = pText; }
		PCSTR		getHiddenText( ) const { return hiddenText;}

	protected:

		EString				hiddenText;

	};




	class aListBox : public aObject
	{
	public:

		aListBox();

		virtual int32_t		init(int32_t xPos, int32_t yPos, int32_t w, int32_t h);
		void				init( FitIniFile* file, PCSTR blockName );

		virtual void		destroy();
		virtual void		render();
		virtual void		update();
		virtual int			handleMessage( ULONG message, ULONG who );
		virtual void	resize(int32_t w, int32_t h);

		virtual int32_t		AddItem(aListItem* itemString);
		virtual int32_t		InsertItem(aListItem* itemString, int32_t where);
		virtual int32_t		RemoveItem( aListItem* itemString, bool bDelete );
		int32_t 				ChangeItemString(short itemNumber, PSTR newString);
		int32_t				GetSelectedItem(void) {return itemSelected;};
		int32_t				GetCheckedItem() const;
		int32_t				SelectItem(int32_t itemNumber);
		bool				IsScrollActive(void) {return scrollActive;};
		int32_t				ActivateScrollbar(void);


		aListItem*			GetItem(int32_t itemNumber);
		int32_t				GetItemCount(){ return itemCount; }

		void				removeAllItems( bool bDelete );

		void				setSpaceBetweenItems( int32_t newSpace ){ skipAmount = newSpace; }
		int32_t				getSpaceBetweenItems(){ return skipAmount; }

		void				setSingleCheck(bool checkOnlyOne){ singleCheck = checkOnlyOne; }

		virtual void		move( float offsetX, float offsetY );
		void				setScrollPos( int pos );

		int32_t				getScrollBarWidth();

		void				setOrange( bool bOrange );
		void				enableAllItems();

		void setPressFX( int newFX ){ clickSFX = newFX; }
		void setHighlightFX( int newFX ){ highlightSFX = newFX; }
		void setDisabledFX( int newFX ){ disabledSFX = newFX; }

		void setTopSkip( int32_t newSkip ){ topSkip = newSkip; }

		bool				pointInScrollBar( int32_t mouseX, int32_t mouseY );
		float				getScrollPos() {return  scrollBar ?  scrollBar->GetScrollPos() : 0; }

	protected:
		int32_t		itemCount;
		int32_t		itemSelected;
		int32_t		skipAmount;

		aListItem*	items[MAX_LIST_ITEMS];
		mcScrollBar*	scrollBar;
		int32_t		itemHeight;
		bool		scrollActive;
		bool		singleCheck;

		int			clickSFX;
		int			highlightSFX;
		int			disabledSFX;
		int			topSkip;


		void		scroll( int amount );
	};


	/* Note that items in an aDropList items do not have to be aTextListItems, whereas in an
	aComboBox they do (well, selectable items do).*/
	class aDropList : public aObject
	{
	public:

		aDropList();

		virtual int32_t	init( FitIniFile* file, PCSTR blockName );
		virtual void	destroy();
		void specialDestroy();
		virtual void		render();
		virtual void		update();
		virtual int			handleMessage( ULONG message, ULONG who );
		virtual bool		pointInside(int32_t xPos, int32_t yPos) const;
		//virtual void	resize(int32_t w, int32_t h);

		virtual int32_t		AddItem(aListItem* itemString);
		int32_t				SelectItem(int32_t item);

		aListBox &ListBox() { return listBox; }
		bool IsExpanded() { return listBox.isShowing(); }
		void IsExpanded(bool isExpanded);
		void disable( bool bDisable ){ 
			if ( bDisable )
				IsExpanded( 0 );
			expandButton.showGUIWindow( !bDisable ); 
			rects[0].showGUIWindow( !bDisable );  rects[1].showGUIWindow( !bDisable );
		}

		int32_t				AddItem( ULONG textID, ULONG color );
		int32_t				AddItem( PCSTR text, ULONG color );
		int32_t				GetSelectedItem() const { return selectionIndex; }

		aDropList& operator=( const aDropList& );


	protected:
		aRect*			rects;
		int32_t			rectCount;
		aAnimButton		expandButton;
		aListBox		listBox;
		float			listBoxMaxHeight;
		int				selectionIndex;
		aAnimTextListItem	templateItem;
		aDropList( const aDropList& );

		int32_t			textLeft;
		int32_t			textTop;

	};


	class aComboBox : public aObject
	{
	public:

		aComboBox();
		~aComboBox() {};

		virtual int32_t	init( FitIniFile* file, PCSTR blockName );
		virtual void	destroy();
		virtual void		render();
		virtual void		update();
		virtual int			handleMessage( ULONG message, ULONG who );
		virtual bool		pointInside(int32_t xPos, int32_t yPos) const;
		//virtual void	resize(int32_t w, int32_t h);

		virtual int32_t		AddItem(aListItem* itemString);
		int32_t				SelectItem(int32_t item);

		void				setReadOnly( bool bReadOnly ){ entry.setReadOnly( bReadOnly ); }
		int32_t				AddItem( ULONG textID, ULONG color );
		int32_t				AddItem( PCSTR text, ULONG color );
		int32_t				GetSelectedItem() const { return selectionIndex; }


		aComboBox& operator=( const aComboBox& );

		aEdit &EditBox() { return entry; }
		aListBox &ListBox() { return listBox; }

		void				setFocus( bool bFocus ) { EditBox().setFocus( bFocus ); }

	protected:
		aEdit		entry;
		aRect*		rects;
		int32_t		rectCount;
		aAnimButton		expandButton;
		aListBox		listBox;
		float		listBoxMaxHeight;
		int				selectionIndex;


		aComboBox( const aComboBox& );
		aAnimTextListItem	templateItem;
	};

}

#endif