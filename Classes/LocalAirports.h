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
//  LocalAirports.h
//  MFBSample
//
//  Created by Eric Berman on 6/2/10.
//  Copyright 2010-2017 MyFlightbook LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MFBWebServiceSvc.h"
#import <sqlite3.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MapKit.h>

@interface LocalAirports : NSObject {
	sqlite3 * database;
	NSMutableArray * rgAirports;
}

@property (nonatomic, assign) sqlite3 * database;
@property (nonatomic, strong) NSMutableArray * rgAirports;

- (instancetype) initWithLocation:(MKCoordinateRegion) loc withDB:(sqlite3 *) db withLimit:(NSInteger) limit NS_DESIGNATED_INITIALIZER;
- (instancetype) initWithAirportList:(NSString *) szAirports withDB:(sqlite3 *) db fromLoc:(CLLocationCoordinate2D) loc NS_DESIGNATED_INITIALIZER;

@end
