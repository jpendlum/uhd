//
// Copyright 2010 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <boost/asio.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <uhd/shared_iovec.hpp>

#ifndef INCLUDED_UHD_TRANSPORT_UDP_HPP
#define INCLUDED_UHD_TRANSPORT_UDP_HPP

namespace uhd{ namespace transport{

class udp : boost::noncopyable{
public:
    typedef boost::shared_ptr<udp> sptr;

    /*!
     * Make a new udp transport.
     * The address will be resolved, it can be a host name or ipv4.
     * The port will be resolved, it can be a port type or number.
     * \param addr a string representing the destination address
     * \param port a string representing the destination port
     * \param bcast if true, enable the broadcast option on the socket
     */
    static sptr make(const std::string &addr, const std::string &port, bool bcast = false);

    /*!
     * Send a vector of buffer (like send_msg).
     * Blocks until the data is sent.
     * \param buffs a vector of asio buffers
     * \return the number of bytes sent
     */
    virtual size_t send(const std::vector<boost::asio::const_buffer> &buffs) = 0;

    /*!
     * Send a single buffer.
     * Blocks until the data is sent.
     * \param buff single asio buffer
     * \return the number of bytes sent
     */
    virtual size_t send(const boost::asio::const_buffer &buff) = 0;

    /*!
     * Receive a buffer. Write into the memory provided.
     * Returns empty when data is not available.
     * \param buff a mutable buffer to receive into
     * \return the number of bytes received.
     */
    virtual size_t recv(const boost::asio::mutable_buffer &buff) = 0;

    /*!
     * Receive a buffer. The memory is managed internally.
     * Returns zero when data is not available.
     * Calling recv will invalidate the buffer of the previous recv.
     * \return a shared iovec with allocated memory
     */
    virtual uhd::shared_iovec recv(void) = 0;
};

}} //namespace

#endif /* INCLUDED_UHD_TRANSPORT_UDP_HPP */