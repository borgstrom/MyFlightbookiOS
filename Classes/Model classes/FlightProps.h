/*
	MyFlightbook for iOS - provides native access to MyFlightbook
	pilot's logbook
 Copyright (C) 2017 MyFlightbook, LLC
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//
//  CustomPropertyType.h
//  MFBSample
//
//  Created by Eric Berman on 7/7/10.
//  Copyright 2010-2017 MyFlightbook LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MFBSoapCall.h"
#import "MFBWebServiceSvc.h"
#import <sqlite3.h>

// known custom property types
#define PropTypeID_NightTakeOff 73 
#define PropTypeID_Solo 77
#define PropTypeID_IPC  41
#define PropTypeID_BFR  44
#define PropTypeID_NameOfPIC    183
#define PropTypeID_NameOfSIC    184
#define PropTypeID_NameOfCFI    92
#define PropTypeID_NameOfStudent    166
#define PropTypeID_TachStart    95
#define PropTypeID_TachEnd      96
#define PropTypeID_ApproachName 267

#define NEW_PROP_ID @-1

@interface FlightProps : NSObject <MFBSoapCallDelegate> {
}

- (BOOL) loadCustomPropertyTypes;
- (BOOL) loadPropertiesForFlight:(NSNumber *) idFlight forUser:(NSString *) szAuthToken;
- (void) deleteProperty:(MFBWebServiceSvc_CustomFlightProperty *) fp forUser:(NSString *) szAuthToken;
- (int) cacheStatus;
- (NSArray *) cachedProps;
- (void) setCacheRetry;
- (NSMutableArray *) propertiesFromDB;

- (MFBWebServiceSvc_CustomPropertyType *) PropTypeFromID:(NSNumber *) id;
- (NSString *) stringValueForProperty:(MFBWebServiceSvc_CustomFlightProperty *) fp;
+ (NSString *) stringValueForProperty:(MFBWebServiceSvc_CustomFlightProperty *) fp withType:(MFBWebServiceSvc_CustomPropertyType *) cpt;

- (NSMutableArray *) distillList:(NSMutableArray *) rgFp includeLockedProps:(BOOL) fIncludeLock;
- (NSMutableArray *) crossProduct:(NSMutableArray *) rgFp;
- (NSMutableArray *) defaultPropList;

- (void) propValueChanged:(MFBWebServiceSvc_CustomFlightProperty *) fp;

- (void) setPropLock:(BOOL) fLock forPropTypeID:(NSInteger) propTypeID;

+ (FlightProps *) getFlightPropsNoNet;

@property (readwrite, strong) NSMutableArray<MFBWebServiceSvc_CustomPropertyType *> * rgPropTypes;
@property (readwrite, strong) MFBWebServiceSvc_ArrayOfCustomFlightProperty * rgFlightProps;
@property (readwrite, strong) NSString * errorString;

@end

// Add methods to MFBWebServiceSvc_CustomPropertyType (from WSDL) to make it conform to the NSCoding protocol
@interface MFBWebServiceSvc_ArrayOfCustomFlightProperty (NSCodingSupport)
- (void)encodeWithCoderMFB:(NSCoder *)encoder;
- (instancetype)initWithCoderMFB:(NSCoder *)decoder;
- (void) setProperties:(NSMutableArray *) ar;
@end

@interface MFBWebServiceSvc_CustomPropertyType (NSCodingSupport)
@property (nonatomic, readwrite) BOOL isLocked;
- (void)encodeWithCoderMFB:(NSCoder *)encoder;
- (instancetype)initWithCoderMFB:(NSCoder *)decoder;
- (instancetype) initFromRow:(sqlite3_stmt *) row;
- (NSString *) description;
@end

@interface MFBWebServiceSvc_CustomFlightProperty (Utility)
- (BOOL) isDefaultForType:(MFBWebServiceSvc_CustomPropertyType *) cpt;
- (void) setDefaultForType:(MFBWebServiceSvc_CustomPropertyType *) cpt;
- (void)encodeWithCoderMFB:(NSCoder *)encoder;
- (instancetype)initWithCoderMFB:(NSCoder *)decoder;
+ (MFBWebServiceSvc_CustomFlightProperty *) getNewFlightProperty;
@end

