/*
* Author: andip71, 02.11.2012
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
*/


#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/charge_level.h>


/* sysfs interface for charge levels */

static ssize_t charge_level_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{

// print current values
return sprintf(buf, "AC charge rate: %d mA \nUSB charge rate: %d mA\n", ac_level, usb_level);

}

static ssize_t charge_level_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

unsigned int ret = -EINVAL;
int tmp_ac_level;
int tmp_usb_level;

// read values from input buffer
ret = sscanf(buf, "%d %d", &tmp_ac_level, &tmp_usb_level);

// check whether values are within the valid ranges and adjust accordingly
if (tmp_ac_level > AC_CHARGE_LEVEL_MAX)
{
tmp_ac_level = AC_CHARGE_LEVEL_MAX;
}

if (tmp_ac_level < AC_CHARGE_LEVEL_MIN)
{
tmp_ac_level = AC_CHARGE_LEVEL_MIN;
}

if (tmp_usb_level > USB_CHARGE_LEVEL_MAX)
{
tmp_usb_level = USB_CHARGE_LEVEL_MAX;
}

if (tmp_usb_level < USB_CHARGE_LEVEL_MIN)
{
tmp_usb_level = USB_CHARGE_LEVEL_MIN;
}

// store values
ac_level = tmp_ac_level;
usb_level = tmp_usb_level;

return count;
}


/* Initialize charge level sysfs folder */

static struct kobj_attribute charge_level_attribute =
__ATTR(charge_level, 0666, charge_level_show, charge_level_store);

static struct attribute *charge_level_attrs[] = {
&charge_level_attribute.attr,
NULL,
};

static struct attribute_group charge_level_attr_group = {
.attrs = charge_level_attrs,
};

static struct kobject *charge_level_kobj;

int charge_level_init(void)
{
int charge_level_retval;

        charge_level_kobj = kobject_create_and_add("charge_level", kernel_kobj);

        if (!charge_level_kobj) {
                return -ENOMEM;
        }

        charge_level_retval = sysfs_create_group(charge_level_kobj, &charge_level_attr_group);

        if (charge_level_retval)
{
         kobject_put(charge_level_kobj);
}

        return (charge_level_retval);
}


void charge_level_exit(void)
{
kobject_put(charge_level_kobj);
}


/* define driver entry points */
module_init(charge_level_init);
module_exit(charge_level_exit);
