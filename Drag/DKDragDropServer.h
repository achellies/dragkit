//
//  DKDragServer.h
//  Drag
//
//  Created by Zac White on 4/20/10.
//  Copyright 2010 Zac White. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "DKDrawerViewController.h"

@protocol DKDragDataProvider

//array of types supported by view.
- (NSArray *)typesForView:(UIView *)dragView;

//request the data from the view.
- (NSData *)dataForType:(NSString *)type forView:(UIView *)dragView;

@end

@protocol DKDropDelegate

//if any of these return YES for the type, the server does its drop drawing.
- (BOOL)targetView:(UIView *)targetView acceptsDropForType:(NSString *)type;
- (void)dragDidEnterTargetView:(UIView *)targetView;
- (void)dragDidLeaveTargetView:(UIView *)targetView;
- (void)dropCompletedOnTargetView:(UIView *)targetView withView:(UIView *)view;

@end

typedef enum {
	DKDrawerVisibilityLevelHidden,
	DKDrawerVisibilityLevelPeeking,
	DKDrawerVisibilityLevelVisible,
} DKDrawerVisibilityLevel;

@interface DKDragDropServer : NSObject {
	UIView *draggedView;
	UIView *originalView;
	
	DKDrawerViewController *drawerController;
	
	DKDrawerVisibilityLevel drawerVisibilityLevel;
	
	// arrays that store the targets and delegates.
	NSMutableArray *dk_dropTargets;
}

+ (id)sharedServer;

- (void)cancelDrag;

@property (nonatomic, retain) UIView *draggedView;
@property (nonatomic, retain) UIView *originalView;

@property (nonatomic, retain) DKDrawerViewController *drawerController;

@property (nonatomic) DKDrawerVisibilityLevel drawerVisibilityLevel;

- (void)markViewAsDraggable:(UIView *)draggableView withDataSource:(NSObject <DKDragDataProvider> *)dropDataSource;
/* Optional parameter for drag identification. */
- (void)markViewAsDraggable:(UIView *)draggableView forDrag:(NSString *)dragID withDataSource:(NSObject <DKDragDataProvider> *)dropDataSource;
- (void)markViewAsDropTarget:(UIView *)dropView withDelegate:(NSObject <DKDropDelegate> *)dropDelegate;

@end
