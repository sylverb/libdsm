// This file is part of libdsm
// Author: Julien 'Lta' BALLET <contact@lta.io>
// Copyright VideoLabs 2014
// License: MIT License

#ifndef __BDSM_NETBIOS_NS_H_
#define __BDSM_NETBIOS_NS_H_

#include "bdsm/netbios_defs.h"
#include "bdsm/netbios_query.h"

#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>


typedef struct                netbios_ns_entry_s
{
  struct netbios_ns_entry_s     *next;
  struct in_addr                address;
  char                          name[NETBIOS_NAME_LENGTH + 2];
}                             netbios_ns_entry_t;

typedef struct {
  int                 socket;
  struct sockaddr_in  addr;
  uint16_t            last_trn_id;  // Last transaction id used;
  netbios_ns_entry_t  *entries;     // Only used during discovery;
}                   netbios_ns_t;

netbios_ns_t  *netbios_ns_new();
void          netbios_ns_destroy(netbios_ns_t *ns);
uint32_t      netbios_ns_resolve(netbios_ns_t *ns, const char *name, char type);
int           netbios_ns_discover(netbios_ns_t *ns);
int           netbios_ns_inverse(netbios_ns_t *ns, netbios_ns_entry_t *entry);

int           netbios_ns_send_query(netbios_ns_t *ns, netbios_query_t *q,
                                    uint32_t ip);
ssize_t       netbios_ns_recv(int sock, void *buf, size_t buf_size,
                              struct timeval *timeout, struct sockaddr *addr,
                              socklen_t *addr_len);

// Remove all the entry from the name service
void                netbios_ns_entry_clear(netbios_ns_t *ns);
// Add an entry to the nameservice list with name and/or ip
netbios_ns_entry_t  *netbios_ns_entry_add(netbios_ns_t *ns, const char *name,
                                          uint32_t ip);
// Find an entry in the list. Search by name if name is not NULL,
// or by ip otherwise
netbios_ns_entry_t  *netbios_ns_entry_find(netbios_ns_t *ns, const char *by_name,
                                           uint32_t ip);

#endif
